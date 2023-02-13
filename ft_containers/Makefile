NAME	= ft_containers
TEST	= std_containers

SRCS	= main.cpp

CC		= c++
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -std=c++98

$(NAME):
			${CC} ${CFLAGS} ${SRCS} -o $@

$(TEST):
			${CC} ${CFLAGS} ${SRCS} -o $@

all:	${NAME} ${TEST}

test:	${TEST}

clean:
		${RM} ${NAME} ${TEST}

fclean:
		${RM} ${NAME} ${TEST}

re:		clean all

.PHONY:	all test clean fclean re
