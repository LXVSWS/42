NAME	= client
NAME2	= server

SRCS	= client.c
SRCS2	= server.c utils.c

OBJS	= ${SRCS:.c=.o}
OBJS2	= ${SRCS2:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
			${CC} ${CFLAGS} -c $< -o $@

$(NAME):	${OBJS} ${OBJS2}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}
			${CC} ${CFLAGS} ${OBJS2} -o ${NAME2}

all:		${NAME} ${NAME2}

clean:
		${RM} ${OBJS} ${OBJS2}

fclean:	clean
		${RM} ${NAME} ${NAME2}

re:		fclean all

.PHONY:	all clean fclean re
