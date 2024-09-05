/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:52:28 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/10 17:52:28 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "minishell.h"

static void	cd_special_case(t_minishell *shell, t_cmd_data *cmd)
{
	char	*path;

	shell->pid[0] = fork();
	if (shell->pid[0] == -1)
		error_msg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE);
	else if (shell->pid[0] == 0)
	{
		redir_to_pipe(shell, cmd);
		path = get_env_var_value(shell->env, shell->pwd);
		if (!path)
			;
		else
			ft_putendl_fd(path, STDOUT_FILENO);
		free_and_exit(shell, EXIT_SUCCESS);
	}
}

int	wait_child(t_minishell *shell)
{
	int	i;
	int	status;
	int	save_status;

	close_pipes(shell);
	i = -1;
	status = 0;
	save_status = 0;
	while (++i < shell->cmd_count - 1)
		waitpid(shell->pid[i], NULL, 0);
	waitpid(shell->pid[i], &save_status, 0);
	if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else
		status = shell->exit_status;
	return (status);
}

void	exec_builtin_without_output(t_minishell *shell, t_cmd_data *cmd)
{
	if (cmd->redir_count)
	{
		redirection_handler(shell, cmd);
		g_sigint_received = 1;
	}	
	else
	{
		g_sigint_received = call_builtin(shell, cmd);
		if (ft_strncmp(shell->cmd_tree[0].cmd, "cd", 3) == 0 && \
			shell->cmd_tree[0].args[0] && g_sigint_received == 0 && \
			ft_strncmp(shell->cmd_tree[0].args[0], "-", 2) == 0)
		{
			cd_special_case(shell, cmd);
			g_sigint_received = wait_child(shell);
		}
	}
}
*/