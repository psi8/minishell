/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:57:16 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/17 22:32:01 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	create_redirection(t_minishell *shell, int n_cmd)
{
	shell->pid[n_cmd] = fork();
	if (shell->pid[n_cmd] == -1)
		error_msg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE);
	else if (shell->pid[n_cmd] == 0)
	{
		redir_to_file(shell, &shell->cmd_tree[n_cmd], EXIT_FAILURE);
		close_fds(cmds, false);
//		free_cmds(cmds);
		free_and_exit(shell, 0);
	}
}

int	exec_child(t_minishell *shell, t_cmd_data *cmd, int num_cmd)
{
//    int num_exec;

	while (num_cmd < shell->cmd_count)
	{
		if (shell->cmd_tree[num_cmd].redir_count)
			redirection_handler(shell, &shell->cmd_tree[num_cmd]);
		if (shell->cmd_tree[num_cmd] && shell->cmd_tree[num_cmd].args[0])
		{
			shell->pid[num_cmd] = fork();
			if (shell->pid[num_cmd] == -1)
				return (error_msg_cmd("fork", NULL, strerror(errno),
						EXIT_FAILURE));
			else if (shell->pid[num_cmd] == 0)
				execute_cmd(shell, num_cmd);
		}
		if (!shell->cmd_tree[num_cmd].cmd[0] && shell->cmd_tree[num_cmd].redir_count)
			create_redirection(shell, num_cmd);
		num_cmd++;
	}
	return (0);
}