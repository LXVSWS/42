/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:10:11 by lwyss             #+#    #+#             */
/*   Updated: 2022/05/31 18:55:43 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	ft_strlen(char *s)
{
	int i = 0;

	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

char *ft_strdup(char *s)
{
	char	*str;
	int		i = ft_strlen(s);

	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * i + 1);
	str[i] = 0;
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

int	exec_cmd(char **av, char **env, int *fd, int flag)
{
	int		pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "error: fatal\n", 13);
		exit(-1);
	}
	if (!pid)
	{
		if (flag == 1)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		else if (flag == 2)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
		}
		if (execve(av[0], av, env) == -1)
		{
			write(2, "error: cannot execute ", 22);
			write(2, av[0], ft_strlen(av[0]));
			write(2, "\n", 1);
			return (-1);
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

char **get_cmd(char **av)
{
	char	**cmd;
	int		i = 0;

	while (av[i] && strcmp(";", av[i]) && strcmp("|", av[i]))
		i++;
	if (!i)
		return (NULL);
	cmd = malloc(sizeof(char *) * i + 1);
	cmd[i] = NULL;
	while (--i >= 0)
		cmd[i] = ft_strdup(av[i]);
	return (cmd);
}

int	pipe_entry(char **input_cmd, char **av, char **env, int old_i)
{
	int	fd[2];
	int	i = 0;
	char **next_cmd;

	if (pipe(fd) == -1)
	{
		write(2, "error: fatal\n", 13);
		return (1);
	}
	next_cmd = get_cmd(av);
	exec_cmd(input_cmd, env, fd, 1);
	close(fd[1]);
	while (av[i] && strcmp(";", av[i]) && strcmp("|", av[i]))
		i++;
	if (av[i] && !strcmp(";", av[i]) && av[i + 1])
		i += old_i + 1;
	else if (av[i] && !strcmp("|", av[i]) && av[i + 1])
		exit(-1);
	else
		i = 0;
	exec_cmd(next_cmd, env, fd, 2);
	close(fd[0]);
	return (i);
}

int	main(int ac, char **av, char **env)
{
	char	**cmd;
	int		i = 1;

	while (ac > 1 && i)
	{
		cmd = get_cmd(&av[i]);
		while (av[i] && strcmp(";", av[i]) && strcmp("|", av[i]))
			i++;
		if (av[i] && !strcmp(";", av[i]) && av[i + 1])
		{
			i++;
			exec_cmd(cmd, env, 0, 0);
		}
		else if (av[i] && !strcmp("|", av[i]) && av[i + 1])
		{
			i++;
			i = pipe_entry(cmd, &av[i], env, i);
		}
		else
		{
			exec_cmd(cmd, env, 0, 0);
			break;
		}
	}
	return (0);
}
