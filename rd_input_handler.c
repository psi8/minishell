/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_input_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:33:21 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/15 21:25:24 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	open_in_file(char *file)
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
