NAME = philo

CFLAGS = -Wall -Werror -Wextra
CC = cc
RM = rm -rf


SRCS = philo.c init.c utils.c free.c action.c check.c
OBJS = $(SRCS:.c=.o)

HEADERS = philosophers.h

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
