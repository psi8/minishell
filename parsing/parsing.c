/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:32:07 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/14 00:51:37 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmd(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if(str[i] == 31)
			count++;
		i++;
	}
	return (count + 1);
}

void	split_pipe(t_minishell *shell, char *str)
{
	int	i;
	int k;

	i = 0;
	k = 0;
	mark_work_pipes(str);
	shell->cmd_count = count_cmd(str);
	tree_init(shell);
	
}

void	line_parse(t_minishell *shell)
{
	promt_init(shell);
	if(shell->status == ERROR)
		return;
	tabs_to_spaces(shell->line);
	if(only_spaces(shell->line))
	{
		shell->line = ERROR;
		return;
	}
	if (quotes_not_closed(shell->line))
	{
		//error(shell, SYNTAX_QUOTES, ERROR, 1);
		return ;
	}
	if (invalid_pipe(shell, shell->line))
		return ;
	split_pipe (shell, shell->line);
}