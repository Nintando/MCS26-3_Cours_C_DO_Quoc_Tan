CC      = gcc
INC_DIR = includes
CFLAGS  = -Wall -Wextra -Werror -I$(INC_DIR)
NAME    = libip2si.a
SRC     = ip_putchar.c ip_putstr.c ip_strlen.c ip_strcmp.c ip_swap.c my_memset.c my_memcpy.c my_memmove.c
OBJ	= $(SRC:.c=.o)

# sources/
SRCS	= $(addprefix sources/,$(src))

# objs/
OBJS	= $(addprefix objs/,$(OBJ))

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

objs/%.o: sources/%.c includes/ip2si.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

re: clean all

