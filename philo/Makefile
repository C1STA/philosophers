NAME = philo

CC = gcc
CFLAGS = -pthread -Wall -Wextra -Werror

SRC = main.c \
	exit.c \
	grim_reaper.c \
	init.c \
	lib.c \
	output.c \
	philosopher.c \
	sim.c \
	time.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	echo "\033[36mMaking philo\033[0m"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -g
	echo "\033[32mDone\033[0m"

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -g

bonus : all

clean :
	echo "\033[35mCleaning philo's objects ...\033[0m"
	rm -f $(OBJ)
	echo "\033[32mDone\033[0m"

fclean :
	make clean
	echo "\033[35mCleaning philo ...\033[0m"
	rm -f $(NAME)
	echo "\033[32mDone\033[0m"

re : fclean
	make all

.PHONY : all clean fclean re bonus
.SILENT :