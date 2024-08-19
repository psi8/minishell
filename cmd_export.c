/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:50:36 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/19 23:00:32 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	print_env(t_minishell *shell)
{
	t_hmap	*env;
	char	*temp_char;
	int		i;

	i = 0;
	if (!shell->hashmap)
		return (EXIT_FAILURE);
	while (shell->hashmap[i])
	{
		env = shell->hashmap[i];
		while (env)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			temp_char = add_quotes(env->key);
			if (temp_char)
				ft_putendl_fd(temp_char, STDOUT_FILENO);
			else
				ft_putendl_fd(env->key, STDOUT_FILENO);
			env = env->next;
			free(temp_char);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	cmd_export(t_minishell *shell, char **argv)
{
	int		result;
	int		index;

	index = 1;
	result = EXIT_SUCCESS;
	if (!argv[1])
	{
		print_env(shell);
		return;
	}
	while (argv[index])
	{
		if (!is_valid_var_name(argv[index]))
		{
			print_arg_err_msg("export", argv[index], "not a valid identifier");
			result = EXIT_FAILURE;
		}
		else
		{
			ft_add_env_hash(shell->hashmap, argv[index], NULL);
		}
		index++;
	}
	shell->exit_status = result;
	return (result);
}
