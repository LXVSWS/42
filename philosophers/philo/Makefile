NAME	= philo

SRCS	= philo.c utils.c utils2.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -g

%.o: %.c
			${CC} ${CFLAGS} -c $< -o $@

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o $@

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
