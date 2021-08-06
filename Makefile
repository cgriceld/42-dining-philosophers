NAME = philo
HEADER = philo.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -pthread

SRC = main.c clean.c setup.c routine.c simulation.c supervisor.c utils.c
OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(SRC) -o $@
	@echo "\033[1;33m RUN : ./philo number_of_philosophers time_to_die
	time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] \033[0m"

clean:
	@/bin/rm -f $(OBJ)
	@echo "\033[1;32m OBJECT FILES DELETED \033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[1;32m EXECUTABLE DELETED \033[0m"

re: fclean all

.PHONY: all clean fclean re