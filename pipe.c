/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:33:47 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/25 12:33:11 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipe_fds(t_minishell *shell, int i)
{
	dup2(shell->pipe[i][1], STDOUT_FILENO);
	dup2(shell->pipe[i - 1][0], STDIN_FILENO);
	close_pipes(shell);
}
