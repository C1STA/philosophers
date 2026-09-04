NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = main.c exit.c supervisor.c init.c lib.c output.c philosopher.c sim.c time.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
