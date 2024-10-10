NAME_SERVER = server
NAME_CLIENT = client

SOURCE_SERVER = server.c helpers.c
SOURCE_CLIENT = client.c helpers.c

OBJECTS_SERVER = $(SOURCE_SERVER:.c=.o)
OBJECTS_CLIENT = $(SOURCE_CLIENT:.c=.o)

CFLAGS = -Wall -Werror -Wextra -I./libft

CC = cc

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJECTS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS_SERVER) $(LIBFT) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJECTS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) --no-print-directory

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJECTS_SERVER) $(OBJECTS_CLIENT)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re