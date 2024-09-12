/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:05:54 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/11 23:05:54 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_wait(t_minishell *sh, int pids);
static void	handle_child_process(t_minishell *sh, t_cmd_data *cmd_data);
/**
 * exec_main - Forks processes and manages their execution in the shell.
 * @sh: Pointer to the main minishell structure.
 */

void	exec_main(t_minishell *sh)
{
	int	process_index;

	process_index = 0;
	signal_toggle((int) 3);
	while (process_index < sh->cmd_count)
	{
		sh->pid[process_index] = fork();
		if (sh->pid[process_index] == -1)
		{
			manage_wait(sh, process_index);
			error_p(sh, "fork", FATAL, 1);
		}
		if (sh->pid[process_index] == 0)
			handle_child_process(sh, &sh->cmd_tree[process_index]);
		process_index++;
	}
	if (sh->cmd_count > 1)
		terminate_pipes(sh);
	manage_wait(sh, sh->cmd_count);
	signal_toggle((int) 1);
}

/**
 * handle_child_process - Executes the child process's commands and redirections.
 * @sh: Pointer to the main minishell structure.
 * @cmd_data: Pointer to the command-specific data.
 */
static void	handle_child_process(t_minishell *sh, t_cmd_data *cmd_data)
{
	signal_toggle(DEFAULT);
	if (sh->cmd_count > 1)
		redirect_to_pipe(sh, cmd_data);
	if (cmd_data->redir_count > 0)
		redirect_to_io(sh, cmd_data, FATAL);
	if (cmd_data->cmd == NULL)
		free_and_exit(sh, 0);
	if (call_builtin(sh, cmd_data))
		free_and_exit(sh, sh->exit_status);
	if (cmd_data->cmd[0])
		validate_command(sh, cmd_data);
	execve(cmd_data->cmd, cmd_data->args, sh->env);
	child_error(sh, ft_strjoin(cmd_data->cmd, NO_CMD), FATAL, 127);
}

/**
 * check_no_children - Checks if there are no active child processes.
 * @sh: Pointer to the main minishell structure.
 * @return: 0 if no children, 1 otherwise.
 */
static int	is_children(t_minishell *sh)
{
	int	process_index;

	process_index = 0;
	while (process_index < sh->cmd_count)
	{
		if (sh->pid[process_index] > 0)
			return (1);
		process_index++;
	}
	return (0);
}

/**
 * manage_wait - Waits for child processes to complete and manages exit statuses.
 * @sh: Pointer to the main minishell structure.
 * @pids: Number of processes to wait for.
 */
static void	manage_wait(t_minishell *sh, int pids)
{
	int	process_index;

	if (!is_children(sh))
		return ;
	process_index = 0;
	while (process_index < pids)
	{
		waitpid(sh->pid[process_index], &sh->exit_status, 0);
		if (WIFSIGNALED(sh->exit_status))
		{
			if (WTERMSIG(sh->exit_status) == SIGQUIT)
				ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
			else if (WTERMSIG(sh->exit_status) == SIGSEGV)
				ft_putstr_fd("Segmentation fault: 11\n", STDERR_FILENO);
			else if (WTERMSIG(sh->exit_status) == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
			sh->exit_status = 128 + WTERMSIG(sh->exit_status);
		}
		process_index++;
	}
}

/*

void	execute_cmd(t_minishell *shell, t_cmd_data *cmd_vars)
{
	signal_toggle(DEFAULT);
	if (shell->cmd_count > 1)
		redir_to_pipe(shell, cmd_vars);
	if (cmd_vars->redir_count > 0)
		redir_to_file(shell, cmd_vars, FATAL);
	if (cmd_vars->cmd == NULL)
		free_and_exit(shell, 0);
	if (is_builtin(cmd_vars->cmd))
		free_and_exit(shell, shell->exit_status);
	if (cmd_vars->cmd[0])
		validate_command(shell, cmd_vars);
	execve(cmd_vars->cmd, cmd_vars->args, shell->env);
	child_error(shell, ft_strjoin(cmd_vars->cmd, NO_CMD), FATAL, 127);
}
*/
