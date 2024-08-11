/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:33:47 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/11 21:40:06 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	checking_pipes(t_commands *cmds, int index)
{
	int	i;

	i = 0;
	if (i == 0)
		i = index;
	if (cmds->operators[i] == PIPE)
	{
		dup2(cmds->pipe[i + 1].fd[1], STDOUT);
	}
}

void	set_pipe_fds(t_commands *cmds, int index)
{
	if (index == 0)
		checking_pipes(cmds, index);
	else
	{
		if (cmds->operators[index])
			checking_pipes(cmds, index);
		if (cmds->operators[index - 1] == PIPE)
			dup2(cmds->pipe[index].fd[0], STDIN);
	}
	close_pipe_fds(cmds);
}
