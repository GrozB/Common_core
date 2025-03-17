NAME	= philo
SRC		= philo.c ft_atoi.c simulation.c
OBJ		= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
