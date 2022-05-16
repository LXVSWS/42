/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 23:47:51 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 14:34:28 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_cmd_words(t_list **lst_tokens, t_params *p)
{
	p->i = 0;
	p->size = 0;
	p->redir_type = 0;
	p->redir_file_type = 0;
	p->cmd = allocate_cmd_size(*lst_tokens);
	p->start_lst = *lst_tokens;
	while (*lst_tokens && get_type((*lst_tokens)->content) != PIPE)
	{
		p->redir_type = get_type((*lst_tokens)->content);
		if (p->redir_type == WORD)
		{
			p->token = (*lst_tokens)->content;
			p->size = ft_strlen(p->token->val);
			p->cmd->cmd_with_args[p->i] = ft_calloc(p->size + 1, sizeof(char));
			ft_strncpy(p->cmd->cmd_with_args[p->i++], p->token->val, p->size);
		}
		else if ((p->redir_type == REDIR_R || p->redir_type == REDIR_RR) && \
		((*lst_tokens)->next && get_type((*lst_tokens)->next->content) == WORD))
		{
			p->token = (*lst_tokens)->next->content;
			close(open(p->token->val, O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO));
			p->redir_file_type = get_type((*lst_tokens)->content);
		}
		*lst_tokens = (*lst_tokens)->next;
	}
}

void	get_cmd_redir(t_params *p)
{
	if (p->redir_type == WORD)
		p->len++;
	else if (p->redir_type == REDIR_R || p->redir_type == REDIR_RR)
		get_cmd_redir_r(p);
	else if (p->redir_type == REDIR_L || p->redir_type == REDIR_LL)
		get_cmd_redir_l(p);
}

void	get_cmd_redir_r(t_params *p)
{
	while (p->i < p->len || !p->len)
	{
		p->cmd->cmd_redir = ft_calloc(p->len + 1, sizeof(t_redir));
		p->cmd->cmd_redir->type = p->redir_file_type;
		if (!p->len)
		{
			p->cmd->file = p->cmd->cmd_with_args[p->i];
			p->i = ft_tab_len(p->cmd->cmd_with_args) - 1;
		}
		else
			p->cmd->file = p->cmd->cmd_with_args[p->i + 1];
		p->cmd->cmd_redir->word = p->cmd->cmd_with_args[p->i++];
		ft_lstadd_back(&p->cmd->redir_out, \
		ft_lstnew((t_redir *)p->cmd->cmd_redir));
		if (!p->len)
			break ;
	}
	p->len = 0;
}

void	get_cmd_redir_l(t_params *p)
{
	while (p->i < p->len || !p->len)
	{
		p->cmd->cmd_redir = ft_calloc(p->len + 1, sizeof(t_redir));
		p->cmd->cmd_redir->type = p->redir_type;
		if (!p->len)
		{
			p->cmd->file = p->cmd->cmd_with_args[p->i];
			p->i = ft_tab_len(p->cmd->cmd_with_args) - 1;
		}
		else
			p->cmd->file = p->cmd->cmd_with_args[p->i + 1];
		p->cmd->cmd_redir->word = p->cmd->cmd_with_args[p->i++];
		ft_lstadd_back(&p->cmd->redir_in, \
		ft_lstnew((t_redir *)p->cmd->cmd_redir));
		if (!p->len)
			break ;
	}
	p->len = 0;
}

t_cmd	*get_cmd_error(t_list **lst_tokens, t_params *p)
{
	if (*lst_tokens)
	{
		*lst_tokens = (*lst_tokens)->next;
		if (!*lst_tokens || get_type((*lst_tokens)->content) == PIPE \
		|| get_type((*lst_tokens)->content) == REDIR_L \
		|| get_type((*lst_tokens)->content) == REDIR_LL \
		|| get_type((*lst_tokens)->content) == REDIR_R \
		|| get_type((*lst_tokens)->content) == REDIR_RR)
		{
			printf("syntax error near unexpected token '|'\n");
			free(p->cmd);
			return (NULL);
		}
	}
	return (p->cmd);
}
