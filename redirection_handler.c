/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:32:35 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/25 12:45:20 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_handler(t_minishell *shell, t_cmd_data *cmd)
{
	int	i;

	i = 0;
	while (cmd->redir[i])
	{
		if (ft_strncmp(cmd->redir[i], ">>", 2) == 0)
			cmd->out = open_out_file(cmd->redir[i] + 2, false);
		else if (ft_strncmp(cmd->redir[i], "<<", 2) == 0)
			heredoc(shell, cmd);
		else if (ft_strncmp(cmd->redir[i], "<", 1) == 0)
			cmd->infile = open_in_file(cmd->redir[i] + 2);
		else if (ft_strncmp(cmd->redir[i], ">", 1) == 0)
			cmd->out = open_out_file(cmd->redir[i] + 2, true);
		if (cmd->out != -1 || cmd->infile != -1)
			break ;
		i++;
	}
}
