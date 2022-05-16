/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 15:51:31 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/16 00:33:48 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	10000
# endif

# ifndef MAX_FD
#  define MAX_FD		65536
#  define FD_MAX		65536
# endif

# define TRUE		1
# define FALSE		0
# define DQUOTE		'"'
# define SQUOTE		'\''

# define RED		"\001\e[0;31m\002"
# define GREEN		"\001\e[0;32m\002"
# define YELLOW		"\001\e[0;33m\002"
# define BLUE		"\001\e[0;34m\002"
# define MAGENTA	"\001\e[0;35m\002"
# define CYAN		"\001\e[0;36m\002"
# define WHITE		"\001\e[0;37m\002"
# define RESET		"\001\e[0m\002"

typedef unsigned long long	t_ull;
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
char		**ft_add_line_tab(char **tab, char *line);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		**ft_copy_tab(char **tab);
char		*ft_del_nl(char *str);
char		*ft_del_at_whitespace(char *str);
char		*ft_free_ptr(char *ptr);
void		ft_free_tab(char **tab);
char		*ft_get_next_line(int fd);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_str_isdigit(char *str);
int			ft_isprint(int c);
int			ft_is_str_blank(char *str);
int			ft_iswhitespace(int c);
void		skip_whitespace(char **line);
void		skip_blank(char **line);
char		*ft_itoa(int n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strchr_nl(const char *s);
char		*ft_strdup(const char *s1);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_free_s1(char *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
size_t		ft_strlen_no_sp(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tab_len(char **tab);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstdel_front(t_list **head);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstdel_next(t_list *current);
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
void		ft_lstprint(t_list *list);
int			ft_lstsize(t_list *lst);
int			ft_printf(const char *format, ...);
void		ft_putchar_nbchr(char c, int *nbchr);
void		ft_putnbr_hex_nbchr(unsigned long nbr, int capitalize, int *nbchr);
void		ft_putnbr_nbchr(long nbr, int *nbchr);
void		ft_putstr_nbchr(char *s, int *nbchr);
char		**ft_lst_to_dpt(t_list *lst);
t_list		*ft_dpt_to_lst(char **tab);
void		ft_lstlink_new(t_list **start, void *to_del, void *new);
void		ft_lstlink_rm(t_list **start, void *data_ref);
t_list		*ft_lst_find_before(t_list *lst, void *data_ref);
t_list		*ft_lst_find(t_list *lst, void *data_ref);
void		ft_putlst(t_list *lst);
int			ft_isin(char *str, int c);
void		ft_print_split(char **split);
void		ft_print_tab(char **tab);
int			ft_bytes_len(int nb);
t_ull		ft_itb(int nb);
void		ft_swap_str(char **a, char **b);
void		ft_swap_content(t_list **a, t_list **b);
size_t		ft_double_strlen(char **arg);
void		ft_free_split(char **tab);
int			ft_bytes_len(int nb);
void		ft_lstdel_content(void *content);
int			ft_atoi_base(const char *str, char *base);
void		ft_void_swap(void *a, void *b);
char		*ft_join_and_free(char *s1, char *s2);
char		*ft_strncat(char *dest, const char *src, size_t n);
int			ft_check_base(char *base);
int			ft_is_prime(int nb);
char		*ft_itoa_base(unsigned long long nb, char *base);
void		ft_putchar(char c);
void		ft_putendl(char const *s);
void		ft_putnbr_base(int nbr, char *base);
void		ft_putnbr(int n);
int			ft_putsize(unsigned long long nb, char *base);
void		ft_putstr(char const *s);
int			*ft_range(int min, int max);
int			ft_recursive_power(int nb, int power);
int			ft_sqrt(int nb);
char		*ft_strcat(char *dest, const char *src);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dest, const char *src);
void		ft_strclr(char *s);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
int			ft_strequ_hd(char const *s1, char const *s2);
char		*ft_strnew(size_t size);
void		ft_strdel(char **as);
void		ft_swap(int *a, int *b);
char		*ft_strnstr_out(const char *str, const char *tofind, size_t n);
int			check_closed_quotes(char *line);

#endif
