NAME	= fractol

SRCS	= fractol.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
			${CC} ${CFLAGS} -Imlx -c $< -o $@

$(NAME):	${OBJS}
			${CC} ${CFLAGS} -Lmlx -lmlx -framework OpenGL -framework AppKit ${OBJS} -o $@

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re

