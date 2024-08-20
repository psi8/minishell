/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:36:38 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/11 21:48:25 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_bool	response_with_quotes(char *cmd);

int	error_msg_cmd(char *cmd, char *detail, char *msg, int status_code)
{
	char	*full_msg;
	bool	is_quotes;

	if (cmd != NULL)
		is_quotes = response_with_quotes(cmd);
	full_msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		full_msg = join_strs(full_msg, cmd);
		full_msg = join_strs(full_msg, ": ");
	}
	if (detail != NULL)
	{
		if (is_quotes)
			full_msg = join_strs(full_msg, "`");
		full_msg = join_strs(full_msg, detail);
		if (is_quotes)
			full_msg = join_strs(full_msg, "'");
		full_msg = join_strs(full_msg, ": ");
	}
	full_msg = join_strs(full_msg, msg);
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
