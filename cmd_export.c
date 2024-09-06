/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:50:36 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/06 23:26:13 by dlevinsc         ###   ########.fr       */
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


/**
 * display_environment - Prints the environment variables with additional formatting.
 * @data: Pointer to the main data structure.
 * @return: EXIT_SUCCESS or EXIT_FAILURE based on the presence of environment variables.
 */
static int display_environment(char **env)
{
    char    *formatted_env;
    int     env_index;

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
//	int		result;
	int		index;

	index = 1;
	if (!argv[index])
	{
		shell->status = display_environment(shell->env);
		return ;
	}
	while (argv[index])
	{
		if (!is_valid_var_name(argv[index]))
			export_error_msg(shell, argv[index]);
		else
			add_to_array(shell, shell->env, argv[index], 1);
		index++;
	}
	return ;
}
