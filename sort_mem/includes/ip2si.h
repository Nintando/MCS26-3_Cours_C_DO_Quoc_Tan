#ifndef IP2SI_H
# define IP2SI_H

#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

// prototypes:
void	ip_putchar(char c);
void	ip_swap(int *a, int *b);
void	ip_putstr(char *str);
int	ip_strlen(char *str);
int	ip_strcmp(char *s1, char *s2);


// Essentials tools (string.h)
void 	*ip_memset(void *dest, int val, size_t n);
void 	*ip_memcpy(void *dest, const void *src, size_t n);
void 	*ip_memmove(void *dest, const void *src, size_t n);

// Project: Sorting & Memory
void    ip_putnbr(int nb);
int     *ip_range(int min, int max);
char    *ip_strdup(char *src);

typedef struct s_magic {
    int     id;
    char    *name;
} t_magic;

void	ip_struct_magic(t_magic *data);
int     ip_magic_number(void *ptr, size_t n, unsigned char magic);

#endif

