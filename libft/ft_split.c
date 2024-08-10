/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:50:06 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/02/15 22:39:43 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clear_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static int	count_words(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		count++;
		while ((str[i] != c) && str[i])
			i++;
	}
	return (count);
}

static char	**fill_array(char **arr, const char *str, char sep)
{
	int	index;
	int	i;
	int	tmp_i;

	index = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == sep)
		{
			i++;
			continue ;
		}
		tmp_i = i;
		while ((str[i] != sep) && str[i])
			i++;
		arr[index] = malloc(i - tmp_i + 1);
		if (!arr[index])
			return (NULL);
		ft_strlcpy(arr[index], str + tmp_i, i - tmp_i + 1);
		index++;
	}
	arr[index] = NULL;
	return (arr);
}

char	**ft_split(char const *str, char c)
{
	char	**array;
	int		words_count;

	if (!str)
		return (NULL);
	words_count = count_words(str, c);
	array = malloc((words_count + 1) * sizeof(char *));
	if (!array)
		return (0);
	array[words_count] = 0;
	if (!fill_array(array, str, c))
	{
		clear_array(array);
		return (NULL);
	}
	return (array);
}
