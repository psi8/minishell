/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:06:20 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/25 12:56:46 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_minishell *shell, t_bool reset_file)
{
	if (shell->pipes_allocated)
	{
		if (shell->std_in != -1) 
			close(shell->std_in);
		if (shell->std_out != -1)
			close(shell->std_out);
		if (reset_file == true)
		{
			;
//			restore_file(cmds->io); should to do
		}
//	close_pipe_fds(shell); // should to do
	}
}

void	free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
