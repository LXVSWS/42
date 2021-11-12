NAME	= tests

SRCS	= tests.c get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42

%.o: %.c
			${CC} ${CFLAGS} -c $< -o $@

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o $@

# -L. - lft -lftprintf

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
