/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:32:07 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/25 12:54:05 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//list of func
static void token (t_minishell *shell, t_cmd_data *cmd);


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

static void substr_create(t_minishell *shell, char *s, int *i)
{
	int	start;
	int	*str;
	
	start = *i;
	while(s[*i] && s[*i] != 31)
		(*i)++;
	str = ft_substr(s, start, *i - start);
	if (!str)
	{
		error();
	}
	if(s[*i])
		(*i)++;
	return(str);
}

static void	split_pipe(t_minishell *shell, char *str)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	mark_work_pipes(str);
	shell->cmd_count = count_cmd(str);
	tree_init(shell);
	while (str[i] && shell->cmd_count && shell->status != ERROR)
	{
		shell->cmd_tree[j].index = j;
		shell->cmd_tree[j].line = substr_create(shell, str, &i);
		token(shell, &shell->cmd_tree[j])
		j++;
	}
	
}

static void token (t_minishell *shell, t_cmd_data *cmd)
{
	if (quotes_not_closed(cmd->line))
	{
		error(shell, SYNTAX_QUOTES, ERROR, 1);
		return ;
	}
	redir_extract(shell, cmd);
	if (cmd->redir_count > 0 && shell->status != ERROR)
		heredoc(shell, cmd);
	
		
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