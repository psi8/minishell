/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_input_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:33:21 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/12 22:52:02 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//static int	open_in_file(t_minishell *shell, char *file);

/*
int	rd_input_handler(t_minishell *shell, char *file)
{
//	char	**red_split;
//	char	*result;
	int		status_code;

//	remove_quotes(file); Pavel do
//	red_split = ft_split(red, '<');
//	result = ft_strtrim(red_split[0], " ");
//	init_io(cmds);
	status_code = open_in_file(shell, file);
//	free_array_str(red_split);
	if (status_code != -1)
		cmds->io->error = true;
	else
		cmds->io->error = false;
	return (status_code);
}
*/

/**
 * @brief Open infile, update the file descriptor. Verify errors to open the
 * file. Will check if the previous in file has error. If yes, does not open
 * any other.
 * @param cmds Commands structure
 */
static int	open_in_file(t_minishell *shell, t_cmd_data cmd, char *file)
{
	int status;

	status = -1;
	if (file && file[0] == '\0')
		return (error_msg_cmd(file, NULL, "ambiguous redirect", false));
	status = open(file, O_RDONLY);
	if (status == -1)
		return (error_msg_cmd(cmds->io->in_file, NULL, strerror(errno), false));
	return (status);
}

bool	remove_old_file_ref(t_io *io, bool in_file)
{
	if (in_file == true && io->in_file)
	{
		if (io->fd_in == -1 || (io->out_file && io->fd_out == -1))
			return (false);
		if (io->heredoc_delimiter != NULL)
		{
			free_ptr(io->heredoc_delimiter);
			io->heredoc_delimiter = NULL;
			unlink(io->in_file);
		}
		free_ptr(io->in_file);
		close(io->fd_in);
	}
	else if (in_file == false && io->out_file)
	{
		if (io->fd_out == -1 || (io->in_file && io->fd_in == -1))
			return (false);
		free_ptr(io->out_file);
		close(io->fd_out);
	}
	return (true);
}
