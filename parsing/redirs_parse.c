/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:17:33 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/11 22:18:11 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//list of func
void		redir_extract(t_minishell *shell, t_cmd_data *cmd);
static int	redir_check(t_minishell *shell, t_cmd_data *cmd);
static char	*get_redir(t_minishell *shell, char *l, int *i);
static void	tidy_fmt(t_minishell *shell, t_cmd_data *cmd, int i);

void	redir_extract(t_minishell *shell, t_cmd_data *cmd)
{
	t_parsed_data	pars;

	init_t_parse(&pars);
	if (redir_check(shell, cmd))
		return ;
	cmd->redir = (char **)malloc(sizeof(char *) * (cmd->redir_count + 1));
	if (!cmd->redir)
		error(shell, ERR_MALLOC, FATAL, 1);
	while (cmd->line[pars.i])
	{
		if (cmd->line[pars.i] == '\'' || cmd->line[pars.i] == '\"')
			pars.i = quotes_skip(cmd->line, pars.i) + 1;
		else if (cmd->line[pars.i] == '>' || cmd->line[pars.i] == '<')
		{
			pars.j = pars.i;
			cmd->redir[pars.k] = get_redir(shell, cmd->line, &pars.i);
			tidy_fmt(shell, cmd, pars.k);
			change_2_space(cmd->line, pars.j, pars.i);
			pars.k++;
		}
		else
			pars.i++;
	}
	cmd->redir[pars.k] = NULL;
}

static int	redir_check(t_minishell *shell, t_cmd_data *cmd)
{
	int	i;

	i = 0;
	while (cmd->line[i])
	{
		if (cmd->line[i] == '\'' || cmd->line[i] == '\"')
			i = quotes_skip(cmd->line, i);
		if (cmd->line[i] == '>' || cmd->line[i] == '<')
		{
			if (cmd->line[i + 1] != '\"' && cmd->line[i + 1] != '\'')
			{
				if (wrong_arrows(shell, cmd->line, cmd->line[i], i + 1))
					return (1);
			}
			if (cmd->line [i + 1] == '>' || cmd->line[i + 1] == '<')
				i++;
			cmd->redir_count++;
		}
		i++;
	}
	if (cmd->redir_count == 0)
		return (1);
	return (0);
}

static char	*get_redir(t_minishell *shell, char *l, int *i)
{
	t_parsed_data	parse;
	char			*str;

	init_t_parse(&parse);
	parse.k = *i;
	while (l[*i] == '>' || l[*i] == '<')
		(*i)++;
	while (l[*i] == ' ')
		(*i)++;
	if (l[*i] == '\'' || l[*i] == '\"')
		*i = quotes_skip(l, *i) + 1;
	while (l[*i] && l[*i] != ' ' && l[*i] != '>' && l[*i] != '<')
		(*i)++;
	str = ft_substr(l, parse.k, *i - parse.k);
	if (!str)
		error(shell, ERR_MALLOC, FATAL, 1);
	return (str);
}

static void	tidy_fmt(t_minishell *shell, t_cmd_data *cmd, int i)
{
	char	*str;

	str = cmd->redir[i];
	if (str[1] == ' ')
	{
		if (str[2] == ' ')
			del_space(&str[2]);
	}
	else if (str[1] == '<' || str[1] == '>')
	{
		if (str[2] == ' ')
			del_space(&str[2]);
	}
	else
	{
		str = add_space(str);
		if (!str)
			error(shell, ERR_MALLOC, FATAL, 1);
	}
	cmd->redir[i] = str;
	quotes_remove(cmd->redir[i]);
}
