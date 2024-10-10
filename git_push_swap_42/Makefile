NAME = push_swap

SOURCE = helpers.c also_helpers.c rotate.c reverse_rotate.c sorting.c \
	also_sorting.c main.c else.c else_2.c lonely.c

OBJECTS = $(SOURCE:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

LIBFT_DIR = ./libft
FT_PRINTF_DIR = ./ft_printf

LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	$(MAKE) -C $(FT_PRINTF_DIR) --no-print-directory

%.o: %.c
	-cc $(CFLAGS) -c $< -o $(<:.c=.o) 

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	rm -f $(NAME)
    
re: fclean all

.PHONY: all clean fclean re
