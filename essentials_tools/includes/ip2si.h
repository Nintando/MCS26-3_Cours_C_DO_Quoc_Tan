#ifndef IP2SI_H
# define IP2SI_H

#include <unistd.h>

// prototypes:
void	ip_putchar(char c);
void	ip_swap(int *a, int *b);
void	ip_putstr(char *str);
int	ip_strlen(char *str);
int	ip_strcmp(char *s1, char *s2);


// Essentials tools (string.h)
void *my_memset(void *dest, int val, size_t n);
void *my_memcpy(void *dest, const void *src, size_t n);
void *my_memmove(void *dest, const void *src, size_t n);

#endif

