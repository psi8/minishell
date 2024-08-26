/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:17:19 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/26 19:04:28 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env(t_minishell *shell, char *search);
void	paths(t_minishell *shell, char **envp);

void	paths(t_minishell *shell, char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if(!ft_strncmp(envp[i], "PATH", 4))
		{
			shell->paths = ft_split(envp[i] + 5, ':');
			if(shell->paths == NULL)
				error();
			return;
		}
		i++;
	}
}

char	*get_env(t_minishell *shell, char *search)
{
	int		i;
	int		len;
	char	*str;
	
	i = 0;
	if (search)
		return (NULL);
	len = ft_strlen(search);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], search, len))
		{
			if (shell->env[i][len] == '=')
			{
				str = ft_strdup(shell->env[i] + len + 1);
				if (str == NULL)
					error(shell, MALLOC_ERR, FATAL, 1);
				return (str);
			}
		}
		i++;
	}
	return (NULL);
}
