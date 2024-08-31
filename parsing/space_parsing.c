/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:38:21 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/31 17:03:47 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tabs_to_spaces(char *str);
int	only_spaces(char *str);
void	change_2_space(char *line, int start, int end);


void	tabs_to_spaces(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if(str[i] == '\'' || str[i] '\"')
			i = quotes_skip(str, i);
		if(str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return(1);
		i++;
	}
	return (1);
}

void	change_2_space(char *line, int start, int end)
{
	while (start < end)
	{
		line[start] = ' ';
		start++;
	}
}