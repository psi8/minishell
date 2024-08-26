/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:22:09 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/26 18:24:29 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char ***array);
int	array_len(char **array);
void	malloc_error(t_minishell *shell, char *str, t_exit_status status);

char	**get_paths(char **env)
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

char	*ft_get_env(t_minishell *shell, char *to_find)
{
	char	*aux;
	int		i;
	int		len;

	i = 0;
	if (!to_find)
		return (NULL);
	len = ft_strlen(to_find);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], to_find, len))
		{
			if (shell->env[i][len] == '=')
			{
				aux = ft_strdup(shell->env[i] + len + 1);
				if (aux == NULL)
					error(shell, ERR_MALLOC, FATAL, 1);
				return (aux);
			}
		}
		i++;
	}
	return (NULL);
}

void	ft_update_pwd(t_minishell *shell)
{
	if (shell->old_pwd)
		free(shell->old_pwd);
	if (shell->pwd)
	{
		shell->old_pwd = ft_strdup(shell->pwd);
		if (!shell->old_pwd)
			error(shell, ERR_MALLOC, FATAL, 1);
	}
	if (shell->pwd)
		free(shell->pwd);
	shell->pwd = getcwd(NULL, 0);
	if (!shell->pwd)
		error(shell, ERR_CWD, ERROR, 1);
//	update_wd_env(shell);
}

char	**add_to_array(t_minishell *shell, char **array, char *new, t_exit_status mode)
{
	int		i;
	char	**new_array;

	i = -1;
	new_array = malloc(sizeof(char *) * (array_len(array) + 2));
	if (!new_array)
		malloc_error(shell, new, mode);
	while (array[++i])
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			free_array(&new_array);
			malloc_error(shell, new, mode);
		}
	}
	new_array[i] = ft_strdup(new);
	if (!new_array[i])
	{
		free_array(&new_array);
		malloc_error(shell, new, mode);
	}
	new_array[i + 1] = NULL;
	free_array(&array);
	return (new_array);
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

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