/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:51:40 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/10 17:51:40 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_pipes(t_commands *cmds, int num_cmd)
{
	int	num_pipes;

	num_pipes = 0;
	while (cmds->operators[num_cmd] && cmds->operators[num_cmd] == PIPE)
	{
		num_cmd = num_cmd + 1;
		num_pipes++;
	}
	return (num_pipes + 1);
}

static void	create_redirection(t_commands *cmds, int num_cmd, t_data *data)
{
	cmds->pid[num_cmd] = fork();
	if (cmds->pid[num_cmd] == -1)
		error_msg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE);
	else if (cmds->pid[num_cmd] == 0)
	{
		if (is_redirection_command(cmds, num_cmd)
			&& check_in_out_file(cmds->io, cmds, true) == false)
			exit_shell(data, EXIT_FAILURE);
		redirect_io(cmds->io, num_cmd);
		close_fds(cmds, false);
		free_cmds(cmds);
		exit_shell(data, 0);
	}
}

int	exec_child(t_data *data, t_commands *cmds, int num_cmd)
{
	cmds->num_exec = cmds->num_exec + count_pipes(cmds, num_cmd);
	while (num_cmd < cmds->num_cmds)
	{
		if (is_redirection_command(cmds, num_cmd))
			redirection_handler(cmds, num_cmd);
		if (cmds->cmds[num_cmd] && cmds->cmd[num_cmd].args[0])
		{
			cmds->pid[num_cmd] = fork();
			if (cmds->pid[num_cmd] == -1)
				return (error_msg_cmd("fork", NULL, strerror(errno),
						EXIT_FAILURE));
			else if (cmds->pid[num_cmd] == 0)
				execute_cmd(data, cmds, num_cmd);
		}
		if (!cmds->cmd[num_cmd].args[0] && cmds->cmd[num_cmd].redirections[0])
			create_redirection(cmds, num_cmd, data);
		if (cmds->operators[num_cmd] && cmds->operators[num_cmd] == PIPE)
			num_cmd++;
		else
			num_cmd = cmds->num_cmds;
	}
	return (0);
}
