/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe_run_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:15:20 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/11 23:38:18 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_pipes(t_minishell *sh);
static void	setup_pipes(t_minishell *sh);

void	process_execution(t_minishell *sh)
{
	if (sh->status == ERROR)
		return ;
	if (sh->cmd_count == 1 && is_builtin(sh->cmd_tree[0].cmd))
	{
		if (sh->cmd_tree[0].redir_count > 0)
		{
			sh->parent_redir = 1;
			sh->std_in = dup(STDIN_FILENO);
			sh->std_out = dup(STDOUT_FILENO);
			redirect_to_io(sh, &sh->cmd_tree[0], ERROR);
		}
		if (sh->status != ERROR)
			call_builtin(sh, &sh->cmd_tree[0]);
		if (sh->parent_redir)
			restore_std(sh);
		return ;
	}
	if (sh->cmd_count > 1)
		initialize_pipes(sh);
	exec_main(sh);
}

/**
 * initialize_pipes - Opens pipes for inter-process communication.
 * @sh: Pointer to the main minishell structure.
 */
static void	initialize_pipes(t_minishell *sh)
{
	int	pipe_index;

	pipe_index = 0;
	setup_pipes(sh);
	while (pipe_index < sh->cmd_count)
	{
		pipe(sh->pipe[pipe_index]);
		if (sh->pipe[pipe_index][0] == -1 || sh->pipe[pipe_index][1] == -1)
			error_p(sh, ERR_PIPE, FATAL, 1);
		pipe_index++;
	}
}

/**
 * setup_pipes - Allocates memory for pipes based on command count.
 * @sh: Pointer to the main minishell structure.
 */
static void	setup_pipes(t_minishell *sh)
{
	int	pipe_index;

	pipe_index = 0;
	sh->pipe = (int **)malloc(sh->cmd_count * sizeof(int *));
	if (sh->pipe == NULL)
		error(sh, ERR_MALLOC, FATAL, 1);
	while (pipe_index < sh->cmd_count)
	{
		sh->pipe[pipe_index] = (int *)malloc(2 * sizeof(int));
		if (!sh->pipe[pipe_index])
			error(sh, ERR_MALLOC, FATAL, 1);
		sh->pipes_allocated++;
		pipe_index++;
	}
}

/**
 * setup_pipes - Allocates memory for the pipe file descriptors 
 * in the minishell instance.
 * @sh: Pointer to the main minishell structure.
 */
void	set_pipe_fds(t_minishell *shell, int i)
{
	dup2(shell->pipe[i][1], STDOUT_FILENO);
	dup2(shell->pipe[i - 1][0], STDIN_FILENO);
	terminate_pipes(shell);
}
