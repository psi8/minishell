/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:17:19 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/25 10:53:52 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	paths(t_minishell *shell, char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if(!ft_strncmp(envp[i], "PATH", 4))
		{
			shell->paths = ft_split(envp[i] + 5, ':');
//			if(shell->paths == NULL) Pavel I comment this only for test
//				error();
			return;
		}
		i++;
	}
}