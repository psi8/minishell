/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:47:38 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/11 22:54:06 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_env(t_minishell *shell, t_cmd_data *cmd)
{
	int		i;

	if (cmd->args[1])
		return (error(shell, "too many arguments", ERROR, 0));
	if (!shell->env)
		return (EXIT_FAILURE);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
