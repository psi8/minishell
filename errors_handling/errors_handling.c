/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:06:45 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/13 23:00:32 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error(t_minishell *shell, char *msg, t_exit_status status, int code)
{
	char	*error_mes;

	if(!msg)
		free_and_exit(shell, 1);
	if(shell->parent_redir)
		
}