NAME = fractol

SOURCE = main.c fractal_render.c colors.c error.c
OBJECTS = $(SOURCE:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g
CC = cc

LIBFT_DIR = ./libft
MINILIBX_DIR = ./minilibx
LIBFT = $(LIBFT_DIR)/libft.a
MLX = -L$(MINILIBX_DIR) -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) --no-print-directory

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re