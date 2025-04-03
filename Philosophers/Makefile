NAME	= philo
SRC		= philo.c ft_atoi.c simulation.c main.c helpers.c philo_actions.c \
			monitor.c init.c
OBJ		= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) -o  $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all