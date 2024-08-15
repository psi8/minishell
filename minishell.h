/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:23:15 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/15 23:56:47 by psitkin          ###   ########.fr       */
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
# include <stdbool.h>
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

//DLevinsc
char **get_paths(char **env);
int         exec_main(t_minishell shell);
bool	    is_builtin_without_output(t_cmd_data *cmd);
void	exec_builtin_without_output(t_minishell shell, t_cmd_data *cmd);
int         cmd_cd(t_minishell *shell, char **argv);
void	cmd_echo(char **argv);
void	cmd_env(t_minishell *shell);
void	cmd_exit(t_minishell *shell, char **argv);
void	cmd_export(t_minishell *shell, char **argv);
void	cmd_pwd(void);
void	close_fds(t_minishell shell, t_bool reset_file);
int	error_msg_cmd(char *cmd, char *detail, char *msg, int status_code);
void	redirection_handler(t_minishell shell, t_cmd_data *cmd);
int	open_out_file(t_minishell shell, int cmd_indx, char *file, bool trunc);

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

#endif