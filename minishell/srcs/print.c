/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:17:31 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/14 00:09:24 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_list *lsttoken)
{
	t_token	*tok;

	if (lsttoken)
		ft_printf("\033[1;34mPRINT TOKENS LIST\n\033[0m");
	while (lsttoken)
	{
		tok = lsttoken->content;
		if (tok->type == WORD)
			ft_printf("\033[1;35mword : *%s*\n\033[0m", tok->val);
		else if (tok->type == PIPE)
			ft_printf("\033[1;35mpipe : *%s*\n\033[0m", tok->val);
		else if (tok->type == REDIR_L)
			ft_printf("\033[1;35m < : *%s*\n\033[0m", tok->val);
		else if (tok->type == REDIR_LL)
			ft_printf("\033[1;35m << : *%s*\n\033[0m", tok->val);
		else if (tok->type == REDIR_R)
			ft_printf("\033[1;35m > : *%s*\n\033[0m", tok->val);
		else if (tok->type == REDIR_RR)
			ft_printf("\033[1;35m >> : *%s*\n\033[0m", tok->val);
		else
			ft_printf("\033[1;35mtoken has invalid type\n\033[0m");
		lsttoken = lsttoken->next;
	}
	ft_printf("\033[1;33m--- ~~~END TOKENS~~~ ---\n\033[0m");
}

void	print_redir(t_list *lstredir)
{
	t_redir	*redir;

	while (lstredir)
	{
		redir = (t_redir *)lstredir->content;
		if (redir->type == REDIR_RR)
			ft_printf("\033[1;33mprint_redir : >> REDIR_RR : %s\n\033[0m", \
			redir->word);
		else if (redir->type == REDIR_R)
			ft_printf("\033[1;33mprint_redir : > REDIR_R : %s\n\033[0m", \
			redir->word);
		else if (redir->type == REDIR_LL)
			ft_printf("\033[1;33mprint_redir : << REDIR_LL : %s\n\033[0m", \
			redir->word);
		else if (redir->type == REDIR_L)
			ft_printf("\033[1;33mprint_redir : < REDIR_L : %s\n\033[0m", \
			redir->word);
		else
			ft_printf("redir has invalid type : %s\n", redir->word);
		lstredir = lstredir->next;
	}
}

void	print_cmd(t_list *lstcmd)
{
	t_cmd	*cmd;
	int		i;

	i = 1;
	while (lstcmd)
	{
		cmd = lstcmd->content;
		ft_printf("\033[1;33mCOMMANDE Num %d :\n\033[0m", i++);
		if (cmd->cmd_with_args)
		{
			ft_printf("\033[1;33m--- args ---\n\033[0m");
			print_strs(cmd->cmd_with_args);
		}
		if (cmd->redir_in)
		{
			ft_printf("\033[1;33m--- redir_in ---\n\033[m");
			print_redir(cmd->redir_in);
		}
		if (cmd->redir_out)
		{
			ft_printf("\033[1;33m--- redir_out ---\n\033[0m");
			print_redir(cmd->redir_out);
		}
		lstcmd = lstcmd->next;
	}
}

void	print_strs(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
		ft_printf("%s\n", strs[i++]);
}

int	error_printer(int ret)
{
	if (ret == BF_ERROR)
		perror("file not found ");
	else if (ret == OP_ERROR)
		perror("file open error ");
	else if (ret == DUP_ERROR)
		perror("dup2 ret error ");
	else if (ret == OUT_ERROR)
		perror("parse error n");
	else if (ret == CMD_ERROR)
		perror("command not found ");
	return (ret);
}
