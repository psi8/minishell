/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:42:29 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/11 22:17:16 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		quotes_skip(char *str, int i);
void	n_terminate(char *str, int i);
int		quotes_not_closed(char *str);
void	quotes_remove(char *str);
void	n_terminate(char *str, int i);

int	quotes_skip(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

int	quotes_not_closed(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (!str[i])
				return (1);
		}
		i++;
	}
	return (0);
}

void	quotes_remove(char *str)
{
	t_parsed_data	parse;

	init_t_parse(&parse);
	while (str[parse.i])
	{
		if (str[parse.i] == '\'' && !parse.inside_doubles)
		{
			parse.inside_singles = !parse.inside_singles;
			parse.i++;
			continue ;
		}
		if (str[parse.i] == '\"' && !parse.inside_singles)
		{
			parse.inside_doubles = !parse.inside_doubles;
			parse.i++;
			continue ;
		}
		str[parse.k] = str[parse.i];
		parse.i++;
		parse.k++;
	}
	n_terminate(str, parse.k);
}

void	n_terminate(char *str, int i)
{
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
}
