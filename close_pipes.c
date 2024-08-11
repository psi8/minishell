/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:37:11 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/11 21:58:03 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_pipe_fds(t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < shell->pipes_allocated)
	{
		if (shell->pipe[i])
		{
			close(shell->pipe[i][0]);
			close(shell->pipe[i][1]);
		}
		i++;
	}
}

void	close_exec_pipe_fds(t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < shell->pipes_allocated)
	{
		if (shell->pipe[i])
		{
			close(cmds->pipe[i][0]);
			close(cmds->pipe[i][1]);
		}
		i++;
	}
}
