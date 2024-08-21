/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:35:23 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/21 17:27:02 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

void	exit_shell(t_data *data, int status_code)
{
	free_data(data, true);
	exit(status_code);
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
	signal_toggle()
}
