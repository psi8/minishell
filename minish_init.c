/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 00:10:06 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/02 00:40:29 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minish_init(t_minishell **shell, char **envp, t_command_data *cmd_data)
{
	int	mode;

	mode = 0;
	*shell = ft_calloc(1, sizeof(t_minishell));
	if (!*shell)
		mode = 200;
	if (mode == 0)
	{
		cmd_data->hmap = init_hmap(envp);
		if (!cmd_data->hmap)
			mode = 200;
	}
	(*shell)->hmap = cmd_data->hmap;
	(*shell)->cmd_data = *cmd_data;
	(*shell)->parent = true;
	add_shlvl(*shell);
	g_sigint_received = 0;
	if (mode != 0)
		terminate_minishell(shell, mode);
}

void	minish_end(t_minishell **shell, int mode)
{
	free_minishell(*shell);
	ft_putstr_fd("Error: Failed to initialize t_minishell"
		"structure\n", STDERR_FILENO);
	exit (mode);
}
