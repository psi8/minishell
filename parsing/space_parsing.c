/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:38:21 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/13 17:44:45 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

