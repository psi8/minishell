/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:36:38 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/11 20:55:08 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_error_msg(t_minishell *shell, char *arg)
{
	char	*error_msg;
	char	*temp;

	temp = ft_strjoin("export: `", arg);
	if (temp == NULL)
		error(shell, ERR_MALLOC, FATAL, 1);
	error_msg = ft_strjoin(temp, "': not a valid identifier");
	free(temp);
	if (error_msg == NULL)
		error(shell, ERR_MALLOC, FATAL, 1);
	error(shell, error_msg, ERROR, 1);
	free(error_msg);
}

void	unset_error_msg(t_minishell *shell, char *arg)
{
	char	*error_msg;
	char	*temp;

	temp = ft_strjoin("unset: `", arg);
	if (temp == NULL)
		error(shell, ERR_MALLOC, FATAL, 1);
	error_msg = ft_strjoin(temp, "': not a valid identifier");
	free(temp);
	if (error_msg == NULL)
		error(shell, ERR_MALLOC, FATAL, 1);
	error(shell, error_msg, ERROR, 1);
	free(error_msg);
}
/*
char *make_err_msg(char *msg)
{
	char	*err_msg;
	char	*temp;

	if (!msg)
		return (NULL);
	temp = ft_strjoin("minishell: ", msg);
	if (!temp)
		return (NULL);
	err_msg = ft_strjoin(temp, "\n");
	if (!err_msg)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (err_msg);
}
*/

char	*make_err_msg_strerr(char *name)
{
	char	*msg;
	char	*temp;
	char	*err_msg;

	msg = ft_strjoin(strerror(errno), "\n");
	if (!msg)
		return (NULL);
	err_msg = ft_strjoin("my_minishell: ", name);
	if (!err_msg)
	{
		free(msg);
		return (NULL);
	}
	temp = ft_strjoin(err_msg, ": ");
	if (!temp)
	{
		free(err_msg);
		free(msg);
		return (NULL);
	}
	free(err_msg);
	err_msg = join_and_free(temp, msg);
	if (!err_msg)
		return (NULL);
	return (err_msg);
}

/**
 * generate_error_message - Creates and returns a formatted error message.
 * @msg: The original error message.
 * @return: A dynamically allocated formatted error message, or NULL on failure.
 */
char	*generate_error_message(char *msg)
{
	char	*formatted_msg;
	char	*temp_msg;

	if (!msg)
		return (NULL);
	temp_msg = ft_strjoin("my_minishell: ", msg);
	if (!temp_msg)
		return (NULL);
	formatted_msg = ft_strjoin(temp_msg, "\n");
	if (!formatted_msg)
	{
		free(temp_msg);
		return (NULL);
	}
	free(temp_msg);
	return (formatted_msg);
}
