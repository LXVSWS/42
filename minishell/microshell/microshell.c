/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:10:11 by lwyss             #+#    #+#             */
/*   Updated: 2022/06/04 18:05:49 by lwyss            ###   ########.fr       */
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

int	exec_cmd(char **av, char **env)
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
		if (execve(av[0], av, env) == -1)
		{
			write(2, "error: cannot execute ", 22);
			write(2, av[0], ft_strlen(av[0]));
			write(2, "\n", 1);
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (1);
}

int	end_pipe(char **av, char **env, int in)
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
		dup2(in, 0);
		close(in);
		if (execve(av[0], av, env) == -1)
		{
			write(2, "error: cannot execute ", 22);
			write(2, av[0], ft_strlen(av[0]));
			write(2, "\n", 1);
		}
	}
	return (1);
}

int	pipex(char **cmd, char **av, char **env, int in, int old_i)
{
	int	pid;
	int	fd[2];
	int i = 0;
	static int j = 0;

	if (pipe(fd) == -1)
	{
		write(2, "error: fatal\n", 13);
		return (1);
	}
	pid = fork();
	if (!pid)
	{
		dup2(in, 0);
		dup2(fd[1], 1);
		close(in);
		close(fd[1]);
		if (execve(cmd[0], cmd, env) == -1)
		{
			write(2, "error: cannot execute ", 22);
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, "\n", 1);
		}
	}
	else
	{
		j++;
		close(fd[1]);
		if (in)
			close(in);
		cmd = get_cmd(av);
		while (av[i] && strcmp(";", av[i]) && strcmp("|", av[i]))
			i++;
		if (av[i] && !strcmp("|", av[i]) && av[i + 1])
			return (pipex(cmd, &av[++i], env, fd[0], old_i));
		else
			j += end_pipe(cmd, env, fd[0]);
		close(fd[0]);
		while (j--)
			waitpid(-1, NULL, 0);
	}
	return (old_i + i);
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
			exec_cmd(cmd, env);
		}
		else if (av[i] && !strcmp("|", av[i]) && av[i + 1])
		{
			i++;
			i = pipex(cmd, &av[i], env, 0, i);
		}
		else
		{
			exec_cmd(cmd, env);
			break;
		}
	}
	system("lsof -c a.out | grep PIPE");
	return (0);
}
