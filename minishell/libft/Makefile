# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/06 15:51:13 by rahmed            #+#    #+#              #
#    Updated: 2022/05/16 00:22:26 by rahmed           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	ft_atoi.c \
			ft_atoll.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_join_and_free.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strchr_nl.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lst_find.c \
			ft_lstiter.c \
			ft_lstlink.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_lst_to_dpt.c \
			ft_printf.c \
			ft_putchar_nbchr.c \
			ft_putnbr_hex_nbchr.c \
			ft_putnbr_nbchr.c \
			ft_putstr_nbchr.c \
			ft_get_next_line.c \
			ft_strchr_nl.c \
			ft_free_ptr.c \
			ft_lstprint.c \
			ft_copy_tab.c \
			ft_del_str.c \
			ft_iswhitespace.c \
			ft_atoi_base.c \
			ft_bytes_len.c \
			ft_check_base.c \
			ft_double_strlen.c \
			ft_free_split.c \
			ft_is_prime.c \
			ft_isin.c \
			ft_itb.c \
			ft_itoa_base.c \
			ft_lstdel_content.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memdel.c \
			ft_print_tab.c \
			ft_putchar.c \
			ft_putendl.c \
			ft_putnbr_base.c \
			ft_putnbr.c \
			ft_putsize.c \
			ft_putstr.c \
			ft_range.c \
			ft_recursive_factorial.c \
			ft_recursive_power.c \
			ft_sqrt.c \
			ft_strcat.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strequ.c \
			ft_strncat.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr_out.c \
			ft_swap_content.c \
			ft_swap_str.c \
			ft_swap.c \
			ft_quote_checker.c 

OBJS		=	${SRCS:.c=.o}

HEADER		=	-I.
CC			=	gcc
RM			=	rm -f
AR			=	ar rcs
CFLAGS		=	-Wall -Wextra -Werror

TXT_RED		=	\033[1;31m
TXT_GREEN	=	\033[1;32m
TXT_YELLOW	=	\033[1;33m
TXT_BLUE	=	\033[1;34m
TXT_MAGENTA	=	\033[1;35m
TXT_CYAN	=	\033[1;36m
FANCY_RESET	=	\033[0m

%.o:		%.c
			@printf "\033[1;34m [OK]\033[1;33m     *** Compiling : ***\033[1;32m      $<\033[1;31m     to\033[1;36m     $@\033[0m                         \r"
			@${CC} -c ${CFLAGS} -o $@ $< ${HEADER}

${NAME}:	${OBJS}
			@echo "${TXT_YELLOW}"
			@${AR} ${NAME} ${OBJS}
			@echo "${FANCY_RESET}"

all:		${NAME}

clean:
			@echo "${TXT_RED}"
			@${RM} ${OBJS}
			@echo "$(FANCY_RESET)"

fclean:		clean
			@echo "${TXT_MAGENTA}"
			@${RM} ${NAME}
			@echo "$(FANCY_RESET)"

re:			fclean all

.PHONY:		all clean fclean re
