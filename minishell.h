/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:23:15 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/26 19:05:07 by psitkin          ###   ########.fr       */
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
void	paths(t_minishell *shell, char **envp);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	redir_extract(t_minishell *shell, t_cmd_data *cmd);
void	init_t_parse(t_parsed_data *parsed);
void	restore_std(t_minishell *shell);
void	pipes_free(t_minishell *shell);
void	array_free(char	***array);
void	tree_free(t_minishell *shell);
void	all_free(t_minishell *shell);
void	free_and_exit(t_minishell *shell, int status);
void	signal_toggle(t_signals status);
void	exit_shell(t_minishell *shell);
int		wrong_arrows(t_minishell *shell, char *line, char arrow, int i);
void	heredoc(t_minishell *shell, t_cmd_data *cmd);
char	*join_and_free(char *str1, char *str2);
char	*make_err_msg_strerr(char *name);
int		heredoc_2_array(t_minishell *shell, char **redir, char **file);
void	expand(t_minishell *shell, char **str);
char	*empty_strdup(t_minishell *shell);
char	*get_env(t_minishell *shell, char *search);

#endif