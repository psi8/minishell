/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:11:35 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/11 23:11:36 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//used func
void	pipes_free(t_minishell *shell);
void	tree_free(t_minishell *shell);
void	array_free(char	***array);

void	all_free(t_minishell *shell)
{
	if (shell->pipes_allocated > 0)
		pipes_free(shell);
	if (shell->pid_allocated)
	{
		free(shell->pid);
		shell->pid_allocated = 0;
	}
	if (shell->paths)
		array_free(&shell->paths);
	if (shell->cmd_tree)
		tree_free(shell);
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
}

void	pipes_free(t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < shell->pipes_allocated)
	{
		free (shell->pipe[i]);
		i++;
	}
	free(shell->pipe);
	shell->pipes_allocated = 0;
}

void	tree_free(t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (shell->cmd_tree[i].line)
		{
			free(shell->cmd_tree[i].line);
			shell->cmd_tree[i].line = NULL;
		}
		if (shell->cmd_tree[i].cmd)
		{
			free(shell->cmd_tree[i].cmd);
			shell->cmd_tree[i].cmd = NULL;
		}
		if (shell->cmd_tree[i].args)
		{
			array_free(&shell->cmd_tree[i].args);
		}
		if (shell->cmd_tree[i].redir)
			array_free(&shell->cmd_tree[i].redir);
		i++;
	}
	free(shell->cmd_tree);
	shell->cmd_tree = NULL;
}

void	array_free(char	***array)
{
	int	i;

	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}
