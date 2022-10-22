NAME	= forms

SRCS	= main.cpp Bureaucrat.cpp Error.cpp Form.cpp ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp

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
