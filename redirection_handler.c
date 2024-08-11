/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:32:35 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/11 21:32:38 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_redirection_command(t_commands *cmds, int i)
{
	if (cmds->cmd[i].redirections[0])
		return (true);
	else
		return (false);
}

void	redirection_handler(t_commands *cmds, int j)
{
	int	i;
	int	status_code;

	i = 0;
	status_code = -1;
	while (cmds->cmd[j].redirections[i])
	{
		if (ft_strncmp(cmds->cmd[j].redirections[i], ">>", 2) == 0)
			status_code = rd_output_handler(cmds, cmds->cmd[j].redirections[i],
					false);
		else if (ft_strncmp(cmds->cmd[j].redirections[i], "<<", 2) == 0)
			rd_heredoc(cmds, cmds->cmd[j].redirections[i]);
		else if (ft_strncmp(cmds->cmd[j].redirections[i], "<", 1) == 0)
			status_code = rd_input_handler(cmds, cmds->cmd[j].redirections[i]);
		else if (ft_strncmp(cmds->cmd[j].redirections[i], ">", 1) == 0)
			status_code = rd_output_handler(cmds, cmds->cmd[j].redirections[i],
					true);
		cmds->io->cmd_index = j;
		if (status_code != -1)
			break ;
		i++;
	}
}
