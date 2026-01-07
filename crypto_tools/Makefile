CC      = gcc
INC_DIR = includes
CFLAGS  = -Wall -Wextra -Werror -I$(INC_DIR)
NAME    = libip2si.a
SRC     = ip_putchar.c \
	  ip_putstr.c \
	  ip_strlen.c \
	  ip_strcmp.c \
	  ip_swap.c \
	  ip_memset.c \
	  ip_memcpy.c \
	  ip_memmove.c \
	  ip_strdup.c \
	  ip_range.c \
	  ip_putnbr.c \
	  ip_struct_magic.c \
	  ip_magic_number.c \
	  ip_iterative_factorial.c \
	  ip_pow.c \
	  simple_xor.c \
	  ip_bin_pack.c \

OBJ	= $(SRC:.c=.o)

# sources/
SRCS	= $(addprefix sources/,$(SRC))

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

