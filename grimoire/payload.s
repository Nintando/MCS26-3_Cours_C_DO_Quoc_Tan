.section .text
.global _start
_start:
    xor %rsi, %rsi      
    push %rsi           
    movabs $0x68732f2f6e69622f, %rdi  
    push $0x3b          # On utilise $ ici car 0x3b est une valeur, pas un registre
    pop %rax            # On utilise % ici car RAX est un registre
    syscall             #
