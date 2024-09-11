/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:55:55 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/11 20:56:24 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error(t_minishell *shell, char *msg, t_exit_status status, int code)
{
	char	*err_msg;

	if (!msg)
		free_and_exit(shell, 1);
	if (shell->parent_redir)
		restore_std(shell);
	err_msg = generate_error_message(msg);
	if (!err_msg)
		free_and_exit(shell, 1);
	else
	{
		write(2, err_msg, ft_strlen(err_msg));
		free(err_msg);
	}
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
		free_and_exit(shell, code);
	return (1);
}

int	error_p(t_minishell *shell, char *msg, t_exit_status status, int code)
{
	char	*err_msg;

	if (!msg)
		free_and_exit(shell, 1);
	if (shell->parent_redir)
		restore_std(shell);
	err_msg = make_err_msg_strerr(msg);
	if (!err_msg)
		free_and_exit(shell, 1);
	else
	{
		write(2, err_msg, ft_strlen(err_msg));
		free(err_msg);
	}
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
		free_and_exit(shell, code);
	return (1);
}

int	child_error(t_minishell *shell, char *msg, t_exit_status status, int code)
{
	char	*error_msg;

	if (!msg)
		free_and_exit(shell, 1);
	if (shell->parent_redir)
		restore_std(shell);
	error_msg = generate_error_message(msg);
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
