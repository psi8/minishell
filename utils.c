/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:22:09 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/10 18:23:18 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#import "minishell.h"

static char	**get_paths(char **env)
{
	size_t	i;
	char	**paths;
	char	*trim_path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i])
	{
		trim_path = ft_substr(env[i], 5, ft_strlen(env[i]));
		paths = ft_split(trim_path, ':');
		free(trim_path);
		return (paths);
	}
	else
		return (NULL);
}