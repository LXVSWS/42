NAME	= libft.a

SRCS	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		  ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
		  ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_strchr.c \
		  ft_putnbr_fd.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
		  ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strrchr.c ft_substr.c ft_itoa.c \
		  ft_strnstr.c ft_strlcpy.c ft_tolower.c ft_toupper.c ft_strtrim.c ft_split.c \

SRCS_B	= $(SRCS) ft_lstadd_back.c ft_lstadd_front.c ft_lstlast.c ft_lstnew.c \
		  ft_lstsize.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS	= ${SRCS:.c=.o}
OBJS_B	= ${SRCS_B:.c=.o}

CC		= gcc
RM		= rm -f
AR		= ar rcs

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
			${CC} ${CFLAGS} -c $< -o $@

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}

all:	${NAME}

bonus:	${OBJS_B}
		${AR} ${NAME} ${OBJS_B}

clean:
		${RM} ${OBJS} ${OBJS_B}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all bonus clean fclean re
