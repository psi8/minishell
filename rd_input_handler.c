/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_input_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:33:21 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/06 22:51:29 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "minishell.h"

int	open_in_file(char *file)
{
	int status;

	status = -1;
	if (file && file[0] == '\0')
		return (error_msg_cmd(file, NULL, "ambiguous redirect", false));
	status = open(file, O_RDONLY);
	if (status == -1)
		return (error_msg_cmd(file, NULL, strerror(errno), false));
	return (status);
}
*/