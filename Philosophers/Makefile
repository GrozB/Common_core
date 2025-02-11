NAME = philosophers

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c src.c utils.c simulation.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
