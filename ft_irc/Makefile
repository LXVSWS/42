NAME	= ircserv

SRCS	= main.cpp Server.cpp

CC		= c++
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -std=c++98

$(NAME):
			${CC} ${CFLAGS} ${SRCS} -o $@

all:	${NAME}

clean:
		${RM} ${NAME}

fclean:
		${RM} ${NAME}

re:		clean all

.PHONY:	all clean fclean re
