NAME	= minishell

SRCS	= minishell.c parsing.c parsing2.c split.c utils.c utils2.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline
# -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib

%.o: %.c
			${CC} ${CFLAGS} -c $< -o $@

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${LFLAGS} ${OBJS} -o $@

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
