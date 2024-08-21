/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 00:12:00 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/21 22:40:30 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_pipe(t_minishell *shell, char *str)
{
	int	i;
	
	i = 0;
	if (starting_pipe(str) || ending_pipe(str))
		return (error);
	while (str[i])
	{
		if(str[i] == '\'' || str[i] == '\"')
			i = quotes_skip(str, i);
		if (str[i] == '|' && str[i + 1])
		{
			i++;
			while (str[i] == ' ')
			{
				i++;
			}
			if (str[i] == '|')
				return (error);
		}
		i++;
	}
	return (0);
}

static int	starting_pipe(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (1);
	return (0);
}

static int	ending_pipe(char *str)
{
	int	i;
	
	i = ft_strlen(str) - 1;
	while (i > 0 && str[i] == ' ')
		i--;
	if (str[i] == '|')
		return (1);
	return (0);
}

void	mark_work_pipe(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = quotes_skip(str, i);
		if (str[i] == '|')
			str[i] = 31;
		i++;
	}
}

int	wrong_arrows(t_minishell *shell, char *line, char arrow, int i)
{
	if (line[i] == '\0')
		return (error(shell, ERR_SYNTAX))
}