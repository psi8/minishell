/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:36:38 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/31 19:44:17 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	response_with_quotes(char *cmd);

int	error_msg_cmd(char *cmd, char *detail, char *msg, int status_code)
{
	char	*full_msg;
	t_bool	is_quotes;

	if (cmd != NULL)
		is_quotes = response_with_quotes(cmd);
	full_msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		full_msg = join_and_free(full_msg, cmd);
		full_msg = join_and_free(full_msg, ": ");
	}
	if (detail != NULL)
	{
		if (is_quotes)
			full_msg = join_and_free(full_msg, "`");
		full_msg = join_and_free(full_msg, detail);
		if (is_quotes)
			full_msg = join_and_free(full_msg, "'");
		full_msg = join_and_free(full_msg, ": ");
	}
	full_msg = join_and_free(full_msg, msg);
	ft_putendl_fd(full_msg, STDERR_FILENO);
	free_ptr(full_msg);
	return (status_code);
}

static t_bool	response_with_quotes(char *cmd)
{
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (true);
	return (false);
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
	err_msg = ft_strjoin("minishell: ", name);
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
