/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:03:54 by rahmed            #+#    #+#             */
/*   Updated: 2022/05/16 00:33:39 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

int		g_exit_status;

enum	e_err
{
	SUCCESS,
	BF_ERROR,
	OP_ERROR,
	DUP_ERROR,
	OUT_ERROR,
	CMD_ERROR
};

enum	e_redir_type
{
	PIPE = 1,
	REDIR_LL,
	REDIR_L,
	REDIR_RR,
	REDIR_R,
	WORD,
};

enum	e_exec_type
{
	EXEC_CHILD,
	EXEC_MAIN,
	EXEC_PIPE,
};

typedef struct s_token
{
	int		type;
	char	*val;
}	t_token;

typedef struct s_redir
{
	int		type;
	char	*word;
}	t_redir;

typedef struct s_env
{
	t_list	*envp;
	char	**path;
	char	**main_env;
	char	*cmd_path;
	int		oldstdin;
	int		stdin;
	int		oldstdout;
	int		stdout;
	int		pid;
	int		pipe_fd[2];
	int		file_fd_in;
	int		file_fd_out;
	int		in_redir;
	int		no_prompt;
	int		no_exec;
	int		no_exit;
	char	current_quote;
}		t_env;

typedef struct s_cmd
{
	char	**cmd_with_args;
	t_redir	*cmd_redir;
	t_list	*redir_in;
	t_list	*redir_out;
	char	*file;
}	t_cmd;

typedef struct s_params
{
	t_token	*token;
	t_cmd	*cmd;
	t_list	*start_lst;
	int		i;
	int		len;
	int		size;
	int		redir_type;
	int		redir_file_type;
}	t_params;

/* builtins_utils.c */
int		get_env_name_len(char *str, int getequal);
int		replace_existing_env(char *args, t_list *env);
char	*ft_get_path(char *args, t_list **env);
char	*ft_get_special_path(char *args, t_list **env);
void	my_chdir(t_list **env, char *path);

/* builtins.c */
int		ft_cmd(char **args, t_env *env, t_cmd *cmd);
void	ft_pwd(void);
void	ft_cd(char **args, t_list **env);
void	ft_pwd_update(t_list **env);
void	ft_env(t_list **env);

/* commands.c */
void	cmds_init(t_list *lstcmd, t_env *env_set);
int		cmds_launcher(t_list *lstcmd, t_env *env_set);
int		cmds_exec(t_list *lstcmd, t_env *env);
int		launch_exec(t_env *env, t_cmd *cmd, int exec);

/* echo.c */
void	ft_echo(char **arg, t_env *env, t_cmd *cmd);
void	ft_print_echo(char **arg, t_env *env, t_cmd *cmd);
int		ft_strequ_echo_n(char const *s1);
void	print_error(char *msg);
int		ft_isbuiltin(char *args);

/* env_check.c */
void	ft_check_unset(char **args, t_list **env);
void	ft_check_export(char **args, t_list **env);
void	ft_print_export(t_list **env);
int		ft_env_alnum_underscore(char *str);
void	ft_check_env(char **args, t_env *env, t_cmd *cmd);

/* env.c */
char	*ft_my_getenv(t_list **env, char *key);
char	*ft_get_env_path(char *args, t_list **env);
void	ft_unset(char *args, t_list **env);
void	ft_export(char *args, t_list **env);
void	ft_write_oldpwd(t_list **env, char *pwd);

/* exec_launcher_utils.c */
void	exec_non_builtin_parent(t_env *env);
char	**ft_set_cmdtoexec(t_cmd *cmd);
char	**ft_set_cmdtoexec_redir(t_cmd *cmd);
char	**ft_set_cmdtoexec_redir_out(t_cmd *cmd);
char	**ft_set_cmdtoexec_redir_in(t_cmd *cmd);

/* exec_launcher.c */
int		exec_in_main(t_cmd *cmd, t_env *env);
int		exec_builtin(t_cmd *cmd, t_env *env);
int		exec_in_child(t_cmd	*cmd, t_env *env);
char	*ft_check_exec_child_cmd(char **cmd, t_env *env);
void	exec_non_builtin_child(char **cmd, t_env *env);

/* get_next_line_exit.c */
char	*ft_get_next_line_exit(int fd);

/* minishell.c */ // * OK
t_env	*env_manager(char **env, t_env *to_free, int finished);
int		routine(t_env *env_set);
int		ft_minishell(t_env *env_set, char *line);
int		ft_exit_code(char **args, int print_exit);
char	**env_maker(char **env);

/* parsing_cmds.c */
int		extract_word(char **line, t_token *token, t_env *env_set);
int		e_word_routine(char **line, t_token *token, t_env *env_set, int i);
t_list	*forge(t_list *tokens);
t_cmd	*get_cmd(t_list **tokens);
char	*get_word(char *line);

/* parsing_get_cmd.c */
void	get_cmd_words(t_list **lst_tokens, t_params *p);
void	get_cmd_redir(t_params *p);
void	get_cmd_redir_r(t_params *p);
void	get_cmd_redir_l(t_params *p);
t_cmd	*get_cmd_error(t_list **lst_tokens, t_params *p);

/* parsing_tokens.c */
t_list	*tokenize(char *line, t_env *env_set);
t_token	*get_token(char **line, t_env *env_set);
void	free_token(void *ptr);
int		check_symbol(char c);
int		extract_symbol(char **line, t_token *token);

/* parsing_utils.c */
int		get_symbol_size(char **line);
int		check_valid_quotes(char *line);
int		get_type(t_token *token);
int		get_word_size_with_quotes(char *line, t_list **env);
int		get_word_size(char *line, t_list **env);

/* parsing_utils2.c */
int		get_fake_env_line_size(char *line, int i);
int		get_line_size(char *line, t_list **env, int i, int *str);
int		get_env_token(char **line, t_token *token, t_list **env, int i);
void	line_checker(char **line, t_token *token, t_env *env_set, int i);
int		squote_token(char **line, t_token *token, t_env *env_set, int i);

/* parsing_utils3.c */
int		env_line_pos(char **line, t_token *token, t_env *env_set, int i);
void	quotes_checker(char **line, t_env *env_set);
int		reset_ended_quotes(char **line, t_token *token, t_env *env_set, int i);
int		prepare_token(char **line, t_token *token, t_list **env);
t_cmd	*allocate_cmd_size(t_list *tokens);

/* pipe.c */
void	ft_pipe(t_cmd *cmd, t_env *env);
void	exec_in_pipe(t_cmd *cmd, t_env *env);
void	ft_check_exec_pipe(t_cmd *cmd, t_env *env);
char	*parse_cmd(char **path, char **cmd);

/* print.c */
void	print_tokens(t_list *lsttoken);
void	print_redir(t_list *lstredir);
void	print_cmd(t_list *lstcmd);
void	print_strs(char **strs);
int		error_printer(int ret);

/* redir.c */
int		redir_heredoc(char *stop, t_env *env);
char	**here_doc(char *stop, t_env *env);
t_list	*heredoc_list_line(char *stop, t_env *env);
int		redir_to_stdout(void *file, int mod, t_env *env);
int		redir_to_stdin(void *file, t_env *env);

/* redir_utils.c */
int		redir_list(t_cmd *cmd, t_list *redir_lst, t_env *env);
int		redir_manager(t_cmd *cmd, t_redir *to_redir, t_env *env);
char	*ft_myreadline(char *prompt);

/* signal.c */
void	init_signal(void);
void	signal_handler(int signo);
int		handle_eof_ctrl_d(char *str);
void	termios_hide_echoctl(void);
void	termios_show_echoctl(void);

#endif
