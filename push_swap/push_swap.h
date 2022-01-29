/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:22:33 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/29 18:31:42 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	int				*content;
	struct s_list	*next;
}	t_list;

size_t	ft_strlen(char const *s);
long	ft_atol(const char *s);
char	**ft_split(char const *s, char c);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	pb(t_list **list_a, t_list **list_b);
void	pa(t_list **list_a, t_list **list_b);
void	sa(t_list **list_a);
void	ra(t_list **list_a);
void	rra(t_list **list_a, int size);
int		test_sort(t_list **list);
void	small_sort(t_list **list_a, int size);
void	bubble_sort(t_list **list);
int		**stock(t_list **list_a, int size);
void	simplify(t_list **list_a, int size);
void	medium_sort(t_list **list_a, t_list **list_b, int size);
void	radix_sort(t_list **list_a, t_list **list_b, int size);
void	free_list(t_list **list);

#endif
