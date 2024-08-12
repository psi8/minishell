/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_output_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:33:00 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/12 22:38:04 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//static int	open_out_file(t_commands *cmds, char *file, bool trunc);

/*
* Pavel did it
int	rd_output_handler(t_minishell shell, t_cmd_data *cmd, char *red, t_bool trunc)
{
	char	**red_split;
	char	*result;
	int		status_code;

	red_split = ft_split(red, '>');
	result = ft_strtrim(red_split[0], " ");
	init_io(cmds);
	status_code = open_out_file(cmds, result, trunc);
	free_array_str(red_split);
	if (status_code != -1)
		cmds->io->error = true;
	else
		cmds->io->error = false;
	return (status_code);
}
*/

int	open_out_file(t_minishell shell, int cmd_indx, char *file, bool trunc)
{
//	if (cmds->io->out_file && cmds->io->out_file[0] == '\0')
//		return (error_msg_cmd(file, NULL, "ambiguous redirect", false));
	int fd;

	fd = -1;
	if (trunc == true)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
		return (error_msg_cmd(file, NULL, strerror(errno), false));
	return (fd);
}
