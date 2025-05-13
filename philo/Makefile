NAME = philo

CFLAGS = -Wall -Werror -Wextra
CC = cc
RM = rm -rf


SRCS = main.c init_utils.c utils.c finish.c begin.c check.c init_total.c begin_utils.c \
	   go_usleep.c error.c
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
