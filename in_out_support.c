/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:30:10 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/11 22:03:18 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	in_out_redirect(t_io *io, int index_cmd)
{
	if (!io || io->cmd_index != index_cmd)
		return ;
	io->std_in_bkp = dup(STDIN_FILENO);
	if (io->std_in_bkp == -1)
		error_msg_cmd("dup", "std-in-bkp", strerror(errno), false);
	io->std_out_bkp = dup(STDOUT_FILENO);
	if (io->std_out_bkp == -1)
		error_msg_cmd("dup", "std-out-bkp", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			error_msg_cmd("dup2", io->in_file, strerror(errno),
				EXIT_FAILURE);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			error_msg_cmd("dup2", io->out_file, strerror(errno),
				EXIT_FAILURE);
}

void	in_out_restore(t_io *io)
{
	if (io->std_in_bkp != -1)
	{
		if (dup2(io->std_in_bkp, STDIN_FILENO) == -1)
			return ;
		close (io->std_in_bkp);
		io->std_in_bkp = -1;
	}
	if (io->std_out_bkp != -1)
	{
		if (dup2(io->std_out_bkp, STDIN_FILENO) == -1)
			return ;
		close (io->std_out_bkp);
		io->std_out_bkp = -1;
	}
}

bool	check_in_out_file(t_io *io, t_commands *cmds, bool free)
{
	if (!io || (!io->in_file && !io->out_file))
		return (true);
	if (((io->in_file && io->fd_in == -1)
			|| (io->out_file && io->fd_out == -1)) && io->error == true)
	{
		if (free)
		{
			close_fds(cmds, false);
			free_cmds(cmds);
		}
		return (false);
	}
	return (true);
}
