/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:25:49 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/12 20:25:55 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std(t_minishell *shell)
{
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
	close(shell->std_in);
	close(shell->std_out);
	shell->parent_redir = 0;
}
