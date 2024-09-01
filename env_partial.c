/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_partial.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:19:25 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/25 11:51:29 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var_value(char **env, char *var)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			result = ft_strchr(env[i], '=') + 1;
			return (result);
		}
		i++;
	}
	free_ptr(tmp);
	return (NULL);
}

void	env_var_remove(t_minishell *shell, int index)
{
	int	i;
	int	j;

	free_ptr(shell->env[index]);
	i = index;
	j = index;
	while (shell->env[i + 1])
	{
		shell->env[i] = ft_strdup(shell->env[i + 1]);
		free_ptr(shell->env[i + 1]);
		j++;
		i++;
	}
	shell->env = env_var_realloc(shell, j);
}

char	**env_var_realloc(t_minishell *shell, int size)
{
	char	**new_env_var;
	int		i;

	i = 0;
	new_env_var = ft_calloc((size + 1), sizeof * new_env_var);
	if (!new_env_var)
		return (NULL);
	while (shell->env[i] && i < size)
	{
		new_env_var[i] = ft_strdup(shell->env[i]);
		free_ptr(shell->env[i]);
		i++;
	}
	free_ptr(shell->env);
	return (new_env_var);
}
