NAME	= cub3D

SRCS	= cub3d.c draw.c parsing.c utils.c utils2.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -g#-fsanitize=address

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
