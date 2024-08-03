/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:51:35 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/03 14:51:35 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pwd(void)
{
	char	path[MAX_PATH];

	if (getcwd(path, MAX_PATH))
	{
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
	{
		perror_err_msg("pwd", NULL);
	}
}
