NAME	= libftprintf.a

SRCS	= ft_printf.c ft_getflag.c ft_putsize.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f
AR		= ar rcs

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
			cd libft && make bonus && mv \
			libft.a ../${NAME} && make clean
			${CC} ${CFLAGS} -c $< -o $@

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
