/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:52:35 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/03 14:52:35 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_unset(t_minishell *shell, char **argv)
{
	int	i;
	int	status_code;

	status_code = EXIT_SUCCESS;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_var_name(argv[i]))
		{
			print_arg_err_msg("unset", argv[i], "not a valid identifier");
			status_code = EXIT_FAILURE;
		}
		else
		{
			ft_remove_env_hash(shell->hashmap, argv[i]);
		}
		i++;
	}
	shell->exit_status = status_code;
}

bool	is_valid_var_name(char *name)
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
