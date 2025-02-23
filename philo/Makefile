RED			= \033[0;31m
CYAN		= \033[0;36m
GREEN		= \033[0;32m
YELLOW	= \033[0;33m
WHITE		= \033[0;37m

NAME = philo
CC = cc
CFLAGS = -pthread -Wall -Wextra -Werror

SRC = main.c exit.c supervisor.c init.c lib.c output.c philosopher.c sim.c time.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(CYAN)Linking $(NAME)...$(WHITE)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Done$(WHITE)"

%.o : %.c
	@$(CC) $(CFLAGS) -c $^

clean:
	@echo "$(RED)Cleaning $(NAME)...$(WHITE)"
	@rm -f $(OBJ)
	@echo "$(GREEN)Done$(WHITE)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re