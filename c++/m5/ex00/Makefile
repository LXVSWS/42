NAME	= bureaucrat

SRCS	= main.cpp Bureaucrat.cpp Error.cpp

CC		= c++
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -std=c++98

$(NAME):
			${CC} ${CFLAGS} ${SRCS} -o $@

all:	${NAME}

clean:
		${RM} ${NAME}

re:		clean all

.PHONY:	all clean re
