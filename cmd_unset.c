/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:52:35 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/06 22:49:37 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_unset(t_minishell *shell, t_cmd_data *cmd, char **args)
{
	int	i;
	int	index;
	int	status_code;

	status_code = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (is_valid_var_name(args[i]) == false)
		{
			unset_error_msg(shell, cmd->args[i]);
			status_code = 1;
		}
		else
		{
			index = get_env_var_index(shell->env, args[i]);
			if (index != -1)
				env_var_remove(shell, index);
		}
		i++;
	}
	return (status_code);
}

t_bool	is_valid_var_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (false);
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
