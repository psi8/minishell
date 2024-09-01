/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:32:07 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/31 17:18:47 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//list of func
static void token (t_minishell *shell, t_cmd_data *cmd);
static int	count_cmd(char *str);
static char *substr_create(t_minishell *shell, char *s, int *i);
void	split_pipe(t_minishell *shell, char *str);
static void token(t_minishell *shell, t_cmd_data *cmd);
void	line_parse(t_minishell *shell);

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

static char *substr_create(t_minishell *shell, char *s, int *i)
{
	int		start;
	char	*str;
	
	start = *i;
	while(s[*i] && s[*i] != 31)
		(*i)++;
	str = ft_substr(s, start, *i - start);
	if (!str)
	{
		error(shell, ERR_MALLOC, FATAL, 1);
	}
	if(s[*i])
		(*i)++;
	return(str);
}

void	split_pipe(t_minishell *shell, char *str)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	mark_working_pipe(str);
	shell->cmd_count = count_cmd(str);
	tree_init(shell);
	while (str[i] && shell->cmd_count && shell->status != ERROR)
	{
		shell->cmd_tree[j].index = j;
		shell->cmd_tree[j].line = substr_create(shell, str, &i);
		token(shell, &shell->cmd_tree[j]);
		j++;
	}
	
}

static void token(t_minishell *shell, t_cmd_data *cmd)
{
	if (quotes_not_closed(cmd->line))
	{
		error(shell, SYNTAX_QUOTES, ERROR, 1);
		return ;
	}
	redir_extract(shell, cmd);
	if (cmd->redir_count > 0 && shell->status != ERROR)
		heredoc(shell, cmd);
	if (shell->status == ERROR)
		return ;
	if (ft_strchr(cmd->line, '$'))
		expand(shell, &cmd->line);
	if (only_spaces(cmd->line))
		return ;
	extract_cmd(shell, cmd);
	extract_args(shell, cmd);
}

void	line_parse(t_minishell *shell)
{
	promt_init(shell);
	if(shell->status == ERROR)
		return;
	tabs_to_spaces(shell->line);
	if(only_spaces(shell->line))
	{
		shell->status = ERROR;
		return;
	}
	if (quotes_not_closed(shell->line))
	{
		error(shell, SYNTAX_QUOTES, ERROR, 1);
		return ;
	}
	if (invalid_pipe(shell, shell->line))
		return ;
	split_pipe (shell, shell->line);
}