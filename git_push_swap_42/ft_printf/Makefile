NAME = libftprintf.a

SOURCES = ft_putstr.c ft_putnbr.c ft_putchar.c ft_printf.c \
		ft_capital_hexadec.c ft_hexadec.c ft_pointer.c ft_strlen.c \
		ft_strrev.c ft_unsigned_dec.c ft_hexadec_long.c ft_memset.c


OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $@ $^
%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
