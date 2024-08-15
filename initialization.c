/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:42:00 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/14 23:29:01 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	promt_init(t_minishell *shell)
{
	shell->pipes_allocated = 0;
	shell->pipe = NULL;
	shell->pid_allocated = 0;
	shell->pid = NULL;
	shell->cmd_count = 0;
	shell->cmd_tree = NULL;
	shell->heredoc_index = 0;
	shell->paths = NULL;
	shell->parent_redir = 0;
}

void	tree_init(t_minishell *shell)
{
	int	i;
	
	i = 0;
	shell->cmd_tree = ((t_cmd_data *)malloc(sizeof(t_cmd) * (shell->cmd_count + 1)));
	if(!shell->cmd_count)
	{
		error(shell, ERR_MALLOC, FATAL, 1);
	}
	
	if(!shell->pid)
		error();
	shell->pid_allocated = 1;
	paths(shell, shell->env);
}