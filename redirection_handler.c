/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:32:35 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/12 22:41:28 by dlevinsc         ###   ########.fr       */
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

void	redirection_handler(t_minishell shell, t_cmd_data *cmd)
{
	int	i;
	int status;

	i = 0;
	while (cmd.redirections[i])
	{
		if (ft_strncmp(cmd.redirections[i], ">>", 2) == 0)
			cmd->out = open_out_file(shell, cmd.redirections[i] + 2);
		else if (ft_strncmp(cmd.redirections[i], "<<", 2) == 0)
			rd_heredoc(cmds, cmds->cmd[j].redirections[i]);
		else if (ft_strncmp(cmd.redirections[i], "<", 1) == 0)
			status = rd_input_handler(shell, cmd.redirections[i] + 2);
		else if (ft_strncmp(cmd.redirections[i], ">", 1) == 0)
			cmd->infile = rd_output_handler(cmds, cmds->cmd[j].redirections[i], true);
		if (cmd->out != -1 || cmd->infile != -1 || status != -1)
			break ;
		i++;
	}
}
