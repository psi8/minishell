/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:33:47 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/12 20:16:50 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * setup_pipes - Allocates memory for the pipe file descriptors in
 * the minishell instance.
 * @sh: Pointer to the main minishell structure.
 */
void	set_pipe_fds(t_minishell *shell, int i)
{
	dup2(shell->pipe[i][1], STDOUT_FILENO);
	dup2(shell->pipe[i - 1][0], STDIN_FILENO);
	close_pipes(shell);
}
