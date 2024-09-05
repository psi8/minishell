/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:06:45 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/05 22:21:45 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
int error(t_minishell *shell, char *msg, t_exit_status status, int code)
{
	if(!msg)
		free_and_exit(shell, 1);
	if(shell->parent_redir)
		code = 1;
	if (code)
		code = 3;
	return status;
}
*/
/*
void	restore_std(t_minishell *shell)
{
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
	close(shell->std_in);
	close(shell->std_out);
	shell->parent_redir = 0;
}
*/
/*
int	child_error(t_minishell *shell, char *msg, t_exit_status status, int code)
{
	code = 0;
	if (!msg)
		free_and_exit(shell, 1);
	if (shell->parent_redir)
		restore_std(shell);
//	error_msg = create_error_msg(msg);
	write(2, "xxx", ft_strlen("XXX"));
	free(msg);
	code = 1; 
	shell->status = status;
	shell->exit_status = code;
//	if (shell->status == FATAL)
//		free_and_exit(shell, code);
	return (code);
}
*/