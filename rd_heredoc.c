/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:33:35 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/31 19:19:37 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_heredoc_to_array(t_minishell *shell, char **redir, char **file)
{
	if (shell->exit_status != 0)
	{
		shell->status = ERROR;
		shell->exit_status = 1;
		free(*file);
		return (1);
	}
	free(*redir);
	*redir = ft_strjoin("< ", *file);
	free(*file);
	if (!*redir)
		error(shell, ERR_MALLOC, FATAL, 1);
	return (0);
}
/*
void	heredoc(t_minishell *shell, t_cmd_data *cmd)
{
	int		i;
	char	*file;
	char *delimiter;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (ft_strncmp(cmd->redir[i], "<<", 2) == 0)
		{
			file = heredoc_filename(shell);
			delimiter = cmd->redir[i] + 2;
			heredoc_prompt(file, delimiter);
			if (add_heredoc_to_array(shell, &cmd->redir[i], &file))
				return ;
			shell->heredoc_index++;
		}
		i++;
	}
}
*/
