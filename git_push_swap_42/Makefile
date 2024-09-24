NAME = push_swap

SOURCE = helpers.c also_helpers.c rotate.c reverse_rotate.c sorting.c \
	also_sorting.c main.c else.c else_2.c

OBJECTS = $(SOURCE:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = cc

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) --no-print-directory

%.o: %.c
	-cc $(CFLAGS) -c $< -o $(<:.c=.o) 

clean: 
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
    
re: fclean all

.PHONY: all clean fclean re
