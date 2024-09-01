/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:50:36 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/26 18:41:39 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
*/

static void	print_env(t_minishell *shell)
{
	int	i;

	i = 0;
	if (!shell->env)
		return ;
	while (shell->env[i])
	{
		printf("declare -x %s\n", shell->env[i]);
		i++;
	}
}

void	cmd_export(t_minishell *shell, char **argv)
{
//	int		result;
	int		index;

	index = 1;
	if (!argv[1])
	{
		print_env(shell);
		return ;
	}
	while (argv[index])
	{
		if (!is_valid_var_name(argv[index]))
		{
			error_msg_cmd("export", argv[index], "not a valid identifier", EXIT_FAILURE);
		}
		else
		{
			add_to_array(shell, shell->env, argv[index], 1);
		}
		index++;
	}
	return ;
}
