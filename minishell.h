/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:23:15 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/19 23:30:32 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef HEREDOC_NAME
#  define HEREDOC_NAME "<<.heredoc_"
# endif

# include <unistd.h>
# include <stdio.h>
# include <signal.h> // signals on Linux
# include <fcntl.h>
# include <stdlib.h>
//# include <stdbool.h>
# include <termios.h> // signals on MAC
# include <errno.h> // eror handling
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include"minishell_struct.h"
# include"errors.h"
# include"libft/libft.h"

extern volatile sig_atomic_t	g_sigint_received;

# define IS_DIR ": is a directory"
# define NO_CMD ": command not found"
# define MAX_PATH 4096

//DLevinsc
char **get_paths(char **env);
int         exec_main(t_minishell *shell);
t_bool	    is_builtin_without_output(t_cmd_data *cmd);
void	exec_builtin_without_output(t_minishell *shell, t_cmd_data *cmd);
int         cmd_cd(t_minishell *shell, char **argv);
int	cmd_echo(char **argv);
int	cmd_env(t_minishell *shell, t_cmd_data *cmd);
int	cmd_exit(t_minishell *shell, char **argv);
int	cmd_export(t_minishell *shell, char **argv);
int	cmd_pwd(void);
int	cmd_unset(t_minishell *shell, char **argv);
void	close_fds(t_minishell shell, t_bool reset_file);
int	error_msg_cmd(char *cmd, char *detail, char *msg, int status_code);
void	redirection_handler(t_minishell shell, t_cmd_data *cmd);
int	open_out_file(char *file, t_bool trunc);
void	heredoc(t_minishell *shell, t_cmd_data *cmd);
int	open_in_file(char *file);
int	call_builtin(t_minishell *shell, t_cmd_data *cmd);
void	redir_to_pipe(t_minishell *shell, t_cmd_data *cmd_vars);
void	redir_to_file(t_minishell *shell, t_cmd_data *c, t_exit_status mode);
char	*get_env_var_value(char **env, char *var);
void	close_pipes(t_minishell *shell);
int	wait_child(t_minishell *shell);
void	execute_cmd(t_minishell *shell, int n_cmd);
void	set_pipe_fds(t_minishell *shell, int i);
void	validate_command(t_minishell *shell, t_cmd_data *cmd_vars);
int	exec_child(t_minishell *shell, t_cmd_data *cmd, int num_cmd);
int	exec_cmd(t_minishell *shell);
int	get_env_var_index(char **env, char *var);
void	env_var_remove(t_minishell *shell, int index);

//Pavel
int		quotes_skip(char *str, int i);
void	tabs_to_spaces(char *str);
int		only_spaces(char *str);
int		quotes_not_closed(char *str);
void	promt_init(t_minishell *shell);
void	split_pipe(t_minishell *shell, char *str);
void	line_parse(t_minishell *shell);
int		invalid_pipe(t_minishell *shell, char *str);
void	mark_work_pipe(char *str);
void	tree_init(t_minishell *shell);
void	free_and_exit(t_minishell *shell, int status);

int	child_error(t_minishell *shell, char *msg, t_exit_status status, int code); //add to test. Pavel you can replace it to your functions

#endif