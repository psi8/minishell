/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:52:18 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/12 20:52:33 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char ***array)
{
	int	i;

	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

void	malloc_error(t_minishell *shell, char *str, t_exit_status status)
{
	if (status == FREEABLE)
		free(str);
	error(shell, ERR_MALLOC, FATAL, 1);
}

char	**array_copy(t_minishell *shell, char **arr)
{
	int		i;
	char	**new_arr;

	i = 0;
	new_arr = malloc(sizeof(char *) * (array_len(arr) + 1));
	if (!new_arr)
		error(shell, ERR_MALLOC, FATAL, 1);
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
		{
			free_array(&new_arr);
			error(shell, ERR_MALLOC, FATAL, 1);
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

int	find_in_array(char **array, char *identifier)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], identifier, ft_strlen(identifier)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	rm_fr_array(char **arr, char *id)
{
	int	i;

	i = 0;
	if (!id || !find_in_array(arr, id))
		return ;
	while (arr[i])
	{
		if (ft_strncmp(arr[i], id, ft_strlen(id)) == 0
			&& (arr[i][ft_strlen(id)] == '\0'
			|| arr[i][ft_strlen(id)] == '='))
		{
			free(arr[i]);
			break ;
		}
		i++;
	}
	if (!arr[i])
		return ;
	while (arr[i + 1])
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[i] = NULL;
}
