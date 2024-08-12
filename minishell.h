/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:23:15 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/12 22:52:12 by dlevinsc         ###   ########.fr       */
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

void		signal_intercept(int status);
static void	interceptor_init(void (*hand_one)(int), void (*hand_two)(int));
void		int_sig_handler(int signum);
void		signal_set(int status);

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

#endif