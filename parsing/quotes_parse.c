/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:42:29 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/31 17:01:51 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_skip(char *str, int i);
void	n_terminate(char *str, int i);
int	quotes_not_closed(char *str);
void	quotes_remove(char *str);
void	n_terminate(char *str, int i);


int	quotes_skip(char *str, int i)
{
	char quote;
	
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
	while(str[i])
	{
		if(str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while(str[i] && str[i] != quote)
				i++;
			if(!str[i])
				return (1);
		}
		i++;
	}
	return (0);
}

void	quotes_remove(char *str)
{
	t_parsed_data	p;

	init_t_parse(&p);
	while (str[p.i])
	{
		if (str[p.i] == '\'' && !p.inside_doubles)
		{
			p.inside_singles = !p.inside_singles;
			p.i++;
			continue ;
		}
		if (str[p.i] == '\"' && !p.inside_singles)
		{
			p.inside_doubles = !p.inside_doubles;
			p.i++;
			continue ;
		}
		str[p.k] = str[p.i];
		p.i++;
		p.k++;
	}
	n_terminate(str, p.k);
}

void	n_terminate(char *str, int i)
{
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
}