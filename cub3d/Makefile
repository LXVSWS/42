NAME	= cub3D

SRCS	= cub3d.c draw.c draw2.c parsing.c split.c texturing.c utils.c utils2.c utils3.c utils4.c utils5.c utils6.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
			${CC} ${CFLAGS} -c $< -o $@

$(NAME):	${OBJS}
			${CC} ${CFLAGS} -Lmlx -lmlx -framework OpenGL -framework AppKit ${OBJS} -o $@

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
