/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:06:20 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/10 18:06:26 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	close_fds(t_commands *cmds, bool reset_io)
{
	if (cmds->io)
	{
		if (cmds->io->fd_in != -1)
			close(cmds->io->fd_in);
		if (cmds->io->fd_out != -1)
			close(cmds->io->fd_out);
		if (reset_io == true)
			restore_io(cmds->io);
	}
	close_pipe_fds(cmds);
}

void	free_io(t_io *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->in_file);
		free_ptr(io->heredoc_delimiter);
	}
	else if (io->in_file)
		free_ptr(io->in_file);
	if (io->out_file)
		free_ptr(io->out_file);
	free_ptr(io);
}

void	free_pipes(t_commands *cmds)
{
	int	i;

	i = 0;
	while (i < cmds->num_cmds)
	{
		free(cmds->pipe[i].fd);
		i++;
	}
	free(cmds->pipe);
}
