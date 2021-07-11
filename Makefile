NAME = philo

HEADER = philosoph.h

SRCS = philosoph.c life_cycle.c utils.c utils_2.c

OBJS = $(SRCS:.c=.o)

GREEN = "\033[0;32m"
CYAN = "\033[0;36m"
RED = "\033[0;31m"
MAGENTA = "\033[0;35m"
EOC = "\033[0m"

CC = @gcc

CFLAGS = -Wall -Wextra -Werror

all:		$(NAME)

%.o:		%.c
				$(CC) $(CFLAGS) -c  $< -o $@

$(NAME):	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
				@echo $(CYAN) "$(NAME) Created!" $(EOC)

clean:
				@rm -f $(OBJS)
				@echo $(GREEN) "Clean complete!" $(EOC)

fclean:		clean
				@rm -f $(NAME)
				@echo $(GREEN) "Fclean complete!" $(EOC)

re:			fclean all

.PHONY:		all clean fclean re