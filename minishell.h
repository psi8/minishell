/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:23:15 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/12 21:38:49 by psitkin          ###   ########.fr       */
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
char	**get_paths(char **env);
void	exec_main(t_minishell *shell);
//t_bool	    is_builtin_without_output(t_cmd_data *cmd);
//void	exec_builtin_without_output(t_minishell *shell, t_cmd_data *cmd);
int		cmd_cd(t_minishell *shell, char **argv);
int		cmd_echo(char **argv);
int		cmd_env(t_minishell *shell, t_cmd_data *cmd);
void	cmd_exit(t_minishell *sh, t_cmd_data *cmd_data);
void	cmd_export(t_minishell *shell, char **argv);
void	cmd_pwd(t_minishell *shell);
int		cmd_unset(t_minishell *shell, t_cmd_data *cmd, char **argv);
//void	close_fds(t_minishell *shell, t_bool reset_file);
void	export_error_msg(t_minishell *shell, char *arg);
void	unset_error_msg(t_minishell *shell, char *arg);
//void	redirection_handler(t_minishell *shell, t_cmd_data *cmd);
//int	open_out_file(char *file, t_bool trunc);
void	heredoc(t_minishell *shell, t_cmd_data *cmd);
//int	open_in_file(char *file);
t_bool	call_builtin(t_minishell *shell, t_cmd_data *cmd);
//void	redir_to_pipe(t_minishell *shell, t_cmd_data *cmd_vars);
void	redirect_to_io(t_minishell *sh, t_cmd_data *cmd, t_exit_status ex_mode);
char	*get_env_var_value(char **env, char *var);

//int	wait_child(t_minishell *shell);
//void	execute_cmd(t_minishell *shell, t_cmd_data *cmd_vars);
//void	set_pipe_fds(t_minishell *shell, int i);
void	validate_command(t_minishell *shell, t_cmd_data *cmd_vars);
//int	exec_child(t_minishell *shell, int num_cmd);
void	process_execution(t_minishell *sh);
int		get_env_var_index(char **env, char *var);
void	env_var_remove(t_minishell *shell, int index);
void	free_ptr(void *ptr);
char	**env_var_realloc(t_minishell *shell, int size);
char	*ft_get_env(t_minishell *shell, char *to_find);
void	ft_update_pwd(t_minishell *shell);
t_bool	is_valid_var_name(char *name);
char	**add_to_array(t_minishell *s, char **a, char *new, t_exit_status m);
t_bool	is_builtin(char *cmd);
//void initialize_pipes(t_minishell *sh);
void	redirect_to_pipe(t_minishell *sh, t_cmd_data *cmd_data);
void	terminate_pipes(t_minishell *sh);

char	*generate_error_message(char *msg);

//FOR TEST
int		child_error(t_minishell *shell, char *msg, t_exit_status st, int code);
//Pavel
int		quotes_skip(char *str, int i);
void	tabs_to_spaces(char *str);
int		only_spaces(char *str);
int		quotes_not_closed(char *str);
void	promt_init(t_minishell *shell);
void	split_pipe(t_minishell *shell, char *str);
void	line_parse(t_minishell *shell);
int		invalid_pipe(t_minishell *shell, char *str);
int		error(t_minishell *shell, char *msg, t_exit_status status, int code);
void	paths(t_minishell *shell, char **envp);
void	mark_working_pipe(char *str);
void	tree_init(t_minishell *shell);
void	paths(t_minishell *shell, char **envp);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	redir_extract(t_minishell *shell, t_cmd_data *cmd);
void	init_t_parse(t_parsed_data *parsed);
void	restore_std(t_minishell *shell);
void	pipes_free(t_minishell *shell);
void	array_free(char	***array);
int		array_len(char **array);
void	tree_free(t_minishell *shell);
void	all_free(t_minishell *shell);
void	free_and_exit(t_minishell *shell, int status);
void	signal_toggle(t_signals status);
void	signals_run_cmd(void);
void	signals_wait_cmd(void);
void	terminate_shell(t_minishell *sh);
int		wrong_arrows(t_minishell *shell, char *line, char arrow, int i);
void	heredoc(t_minishell *shell, t_cmd_data *cmd);
char	*join_and_free(char *str1, char *str2);
char	*make_err_msg_strerr(char *name);
int		heredoc_2_array(t_minishell *shell, char **redir, char **file);
void	expand(t_minishell *shell, char **str);
char	*empty_strdup(t_minishell *shell);
char	*get_env(t_minishell *shell, char *search);
int		error_p(t_minishell *shell, char *msg, t_exit_status status, int code);
int		quotes_skip(char *str, int i);
void	n_terminate(char *str, int i);
int		quotes_not_closed(char *str);
void	quotes_remove(char *str);
void	n_terminate(char *str, int i);
void	change_2_space(char *line, int start, int end);
void	del_space(char *str);
char	*add_space(char *str);
void	extract_cmd(t_minishell *shell, t_cmd_data *cmd);
void	extract_args(t_minishell *shell, t_cmd_data *cmd);
char	**array_copy(t_minishell *shell, char **array);
void	shlvl_increment(t_minishell *shell);
void	rm_fr_array(char **arr, char *id);
void	shell_init(t_minishell *shell, char **envp);

#endif