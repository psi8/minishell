/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:47:38 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/03 14:47:38 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_env(t_minishell *shell)
{
	t_hmap	*env;
	int		i;

	if (!shell->hashmap)
	{
		print_err_msg("env: environment not found");
		return;
	}
	for (i = 0; shell->hashmap[i]; i++)
	{
		env = shell->hashmap[i];
		while (env)
		{
			if (ft_strchr(env->key, '='))
			{
				ft_putstr_fd(env->key, STDOUT_FILENO);
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putendl_fd(env->value, STDOUT_FILENO);
			}
			env = env->next;
		}
	}
}
