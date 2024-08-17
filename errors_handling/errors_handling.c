/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:06:45 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/17 22:20:29 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error(t_minishell *shell, char *msg, t_exit_status status, int code)
{
	char	*error_mes;

	if(!msg)
		free_and_exit(shell, 1);
	if(shell->parent_redir)
		
}

/*
* Copy two that functions without changes. Only for test. 
* Pavel you can replace their on your functions
*
*/

static void	restore_std(t_minishell *shell)
{
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
	close(shell->std_in);
	close(shell->std_out);
	shell->parent_redir = 0;
}

int	child_error(t_minishell *shell, char *msg, t_exit_status status, int code)
{
	char	*error_msg;

	if (!msg)
		free_and_exit(shell, 1);
	if (shell->parent_redir)
		restore_std(shell);
	error_msg = create_error_msg(msg);
	if (!error_msg)
		free_and_exit(shell, 1);
	else
	{
		write(2, error_msg, ft_strlen(error_msg));
		free(error_msg);
	}
	free(msg);
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
		free_and_exit(shell, code);
	return (1);
}