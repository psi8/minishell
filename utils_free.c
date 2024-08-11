/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:06:20 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/11 21:30:55 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	free_pipes(t_commands *cmds);
void	free_io(t_io *io);

void	close_fds(t_minishell shell, t_bool reset_file)
{
	if (shell->pipes_allocated)
	{
		if (shell->std_in != -1) 
			close(shell->std_in);
		if (shell->std_out != -1)
			close(shell->std_out);
		if (reset_file == true)
			restore_file(cmds->io);
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
