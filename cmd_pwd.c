/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:51:35 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/19 23:02:37 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_pwd(void)
{
	char	*pwd;
	char	path[MAX_PATH];

	pwd = getcwd(path, MAX_PATH);
	if (pwd)
	{
		ft_putendl_fd(path, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	error_msg_cmd("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
