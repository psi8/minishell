/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe_run_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:02:06 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/17 22:44:56 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmds(t_minishell *shell);
static void	init_pipe(t_minishell *shell);

static int	exec_cmd(t_minishell *shell)
{
	int			status_code;

	shell->exit_status = 0;
	status_code = 0;
	init_cmds(shell);
	shell->exit_status = exec_main(shell);
	if (status_code == 0 && shell->exit_status != 0)
		status_code = shell->exit_status;
	close_fds(shell, false);
//	free_cmds(shell);
	return (status_code);
}

static void	init_pipe(t_minishell *shell)
{
	int	i;

	i = 0;
	shell->pipe = ft_calloc(shell->cmd_count, sizeof(* int));
	while (i < shell->cmd_count)
	{
		shell->pipe[i] = ft_calloc(sizeof(int), 2);
		if (!shell->pipe[i])
			exit(6);
		i++;
	}
}

void	init_cmds(t_minishell *shell)
{
	int		i;

	i = 0;
	if (shell->exit_status == 0)
	{
		shell->paths = get_paths(shell->env);
		init_pipe(shell);
		shell->pid = (int *)ft_calloc(sizeof(int *), shell->cmd_count + 1);
//		shell->cmd_tree = (t_cmd_data *) ft_calloc(sizeof(t_cmd_data *), shell->cmd_count + 1); //Pavel initializes it
	}
}

