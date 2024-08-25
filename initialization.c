/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:42:00 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/25 10:52:58 by dlevinsc         ###   ########.fr       */
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

static void	cmd_init(t_cmd_data *cmd)
{
	cmd->arg_count = 0;
	cmd->args = NULL;
	cmd->cmd = NULL;
	cmd->index = 0;
	cmd->infile = -2;
	cmd->out = -2;
	cmd->line = NULL;
	cmd->redir = NULL;
	cmd->redir_count = 0;
}

void	tree_init(t_minishell *shell)
{
	int	i;
	
	i = 0;
	shell->cmd_tree = ((t_cmd_data *)malloc(sizeof(t_cmd_data) * (shell->cmd_count + 1)));
	if(!shell->cmd_count)
	{
		error(shell, ERR_MALLOC, FATAL, 1);
	}
	while(i < shell->cmd_count)
	{
		cmd_init(&shell->cmd_tree[i]);
		i++;
	}
	shell->cmd_tree[i].line = NULL;
	shell->pid = (int *)malloc(sizeof(int) * shell->cmd_count);
	if(!shell->pid)
		error(shell, ERR_MALLOC, FATAL, 1);
	shell->pid_allocated = 1;
	shell->paths = get_paths(shell->env); //Pavel, I correct this (only for test), but you can use your version.
}