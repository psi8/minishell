/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:50:32 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/11 21:50:33 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		expand(t_minishell *shell, char **str);
static void	exp_env(t_minishell *shell, char **str, int *i);
static int	fin_char(char c);
static char	*get_exp(t_minishell *shell, char *str);
static char	*get_exit_status(t_minishell *shell);

void	expand(t_minishell *shell, char **str)
{
	int		i;
	int		in_doubles;

	if (shell->status == ERROR)
		return ;
	i = 0;
	in_doubles = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\"')
			in_doubles = !in_doubles;
		if ((*str)[i + 1] && (*str)[i] == '\'' && !in_doubles)
			i = quotes_skip(*str, i);
		if ((*str)[i + 1] && (*str)[i] == '$' && (*str)[i + 1] != ' ')
		{
			exp_env(shell, str, &i);
			continue ;
		}
		i++;
	}
}

static void	exp_env(t_minishell *shell, char **str, int *i)
{
	char	*new;
	char	*value;
	int		start;

	(*i)++;
	start = *i;
	if (fin_char((*str)[start]) && (*str)[start + 1] == '\0')
		return ;
	value = get_exp(shell, &(*str)[start]);
	(*i) = start + ft_strlen(value) - 1;
	new = join_and_free(ft_substr(*str, 0, start - 1), value);
	if (!new)
		error(shell, ERR_MALLOC, FATAL, 1);
	if ((*str)[start] != '?')
		while (!fin_char((*str)[start]))
			start++;
	else
		start++;
	if ((*str)[start])
		new = join_and_free(new, ft_strdup(&(*str)[start]));
	if (!new)
		error(shell, ERR_MALLOC, FATAL, 1);
	free(*str);
	*str = new;
}

static int	fin_char(char c)
{
	if (c == '\0' || c == ' ' || c == '/' || c == '$' || c == '\"'
		|| c == '\'' || c == '=' || c == ':' || c == '@')
		return (1);
	return (0);
}

static char	*get_exp(t_minishell *shell, char *str)
{
	char	*env;
	char	*val;
	int		l;

	l = 0;
	if (str[l] == '?')
		return (get_exit_status(shell));
	while (!fin_char(str[l]))
		l++;
	if (l == 0)
		return (empty_strdup(shell));
	env = ft_substr(str, 0, l);
	if (!env)
		error(shell, ERR_MALLOC, FATAL, 1);
	val = get_env(shell, env);
	if (!val)
		val = empty_strdup(shell);
	free(env);
	return (val);
}

static char	*get_exit_status(t_minishell *shell)
{
	char	*value;

	if (shell->exit_status > 255)
		value = ft_itoa(WEXITSTATUS(shell->exit_status));
	else
		value = ft_itoa(shell->exit_status);
	if (!value)
		error(shell, ERR_MALLOC, FATAL, 1);
	return (value);
}
