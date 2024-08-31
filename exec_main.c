/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:49:38 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/10 17:49:38 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_main(t_minishell *shell)
{
	int	status_code;
	int	g_status_code;
	int i;

	i = -1;
	status_code = 0;
	while (++i < shell->cmd_count)
	{
		if (shell->cmd_tree[i].cmd[0] && is_builtin_without_output(&shell->cmd_tree[i]))
			exec_builtin_without_output(shell, &shell->cmd_tree[i]);
		else
		{
			status_code = exec_child(shell, i);
			g_status_code = wait_child(shell);
			if (status_code != 0)
				g_status_code = status_code;
		}
	}
	return (g_status_code);
}


void	execute_cmd(t_minishell *shell, t_cmd_data *cmd_vars)
{
	signal_toggle(DEFAULT);
	if (shell->cmd_count > 1)
		redir_to_pipe(shell, cmd_vars);
	if (cmd_vars->redir_count > 0)
		redir_to_file(shell, cmd_vars, FATAL);
	if (cmd_vars->cmd == NULL)
		free_and_exit(shell, 0);
	if (call_builtin(shell, cmd_vars))
		free_and_exit(shell, shell->exit_status);
	if (cmd_vars->cmd[0])
		validate_command(shell, cmd_vars);
	execve(cmd_vars->cmd, cmd_vars->args, shell->env);
	child_error(shell, ft_strjoin(cmd_vars->cmd, NO_CMD), FATAL, 127);
}

