/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:02:54 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/13 15:30:56 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_in_env(char **env, char *id);

static char	*add_quotes(char *env)
{
	int		i;
	int		o;
	char	*temp_char;

	o = 0;
	while (env[o] && env[o++] != '=')
		;
	if (!env[o] && env[o - 1] != '=')
		return (NULL);
	temp_char = malloc(sizeof(char) * ft_strlen(env) + 3);
	temp_char[ft_strlen(env) + 2] = '\0';
	i = 0;
	o = 0;
	while (env[o] != '=')
		temp_char[i++] = env[o++];
	temp_char[i++] = env[o++];
	temp_char[i++] = '"';
	while (env[o])
		temp_char[i++] = env[o++];
	temp_char[i++] = '"';
	return (temp_char);
}

/**
 * display_environment - Prints the environment variables with
 * additional formatting.
 * @data: Pointer to the main data structure.
 * @return: EXIT_SUCCESS or EXIT_FAILURE based on the presence
 * of environment variables.
 */
static int	display_environment(char **env)
{
	char	*formatted_env;
	int		env_index;

	env_index = 0;
	if (!env)
		return (EXIT_FAILURE);
	while (env[env_index])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		formatted_env = add_quotes(env[env_index]);
		if (formatted_env)
			ft_putendl_fd(formatted_env, STDOUT_FILENO);
		else
			ft_putendl_fd(env[env_index], STDOUT_FILENO);
		env_index++;
		free(formatted_env);
	}
	return (EXIT_SUCCESS);
}

void	cmd_export(t_minishell *shell, char **argv)
{
	int	index;

	index = 1;
	if (!argv[index])
	{
		display_environment(shell->env);
		return ;
	}
	while (argv[index])
	{
		if (!is_valid_var_name(argv[index]))
			export_error_msg(shell, argv[index]);
		else
		{
			if (!is_in_env(shell->env, argv[index]))
				shell->env = add_to_array(shell, shell->env, argv[index], 0);
		}
		index++;
	}
	return ;
}

static t_bool	is_in_env(char **env, char *id)
{
	int	i;
	int	len;

	if (!env || !id)
		return (false);
	len = 0;
	while (id[len] && id[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], id, len) == 0 && env[i][len] == '=')
			return (true);
		i++;
	}
	return (false);
}
