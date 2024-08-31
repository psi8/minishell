/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:38:21 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/31 18:14:46 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tabs_to_spaces(char *str);
int	only_spaces(char *str);
void	change_2_space(char *line, int start, int end);
char	*add_space(char *str);
void	del_space(char *str);


void	tabs_to_spaces(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if(str[i] == '\'' || str[i] == '\"')
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

void	del_space(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
		str[j++] = str[i++];
	str[j] = '\0';
}

char	*add_space(char *str)
{
	char	*new;

	if (str[0] == '<')
		new = ft_strjoin("< ", &str[1]);
	else
		new = ft_strjoin("> ", &str[1]);
	if (!new)
		return (NULL);
	free(str);
	return (new);
}