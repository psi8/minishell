/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:42:29 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/13 18:03:43 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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