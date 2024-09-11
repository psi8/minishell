/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:58:08 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/11 20:59:01 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * terminate_shell - Exits the minishell, freeing resources and printing 
 * the exit message.
 * @sh: Pointer to the main minishell structure.
 */
void	terminate_shell(t_minishell *sh)
{
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	array_free(&sh->env);
	all_free(sh);
	signal_toggle(DEFAULT);
	exit(sh->exit_status);
}

void	free_and_exit(t_minishell *shell, int status)
{
	if (shell->parent_redir)
		restore_std(shell);
	all_free(shell);
	array_free(&shell->env);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->old_pwd)
		free(shell->old_pwd);
	signal_toggle(DEFAULT);
	exit(status);
}
