NAME	= libftprintf.a

SRCS	= ft_printf.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f
AR		= ar rcs

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
			cd libft && make bonus && \
			mv libft.a .. && make clean
			${CC} ${CFLAGS} -c $< -o $@

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME} libft.a

re:		fclean all

.PHONY:	all clean fclean re
