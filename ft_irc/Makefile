NAME	= ircserv

SRCS	= main.cpp Client.cpp Server.cpp Channel.cpp Command.cpp

CC		= c++
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

$(NAME):
			${CC} ${CFLAGS} ${SRCS} -o $@

all:	${NAME}

clean:
		${RM} ${NAME}

fclean:
		${RM} ${NAME}

re:		clean all

.PHONY:	all clean fclean re
