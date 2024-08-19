/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:45:12 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/19 22:48:29 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	exist_n_option(char **argv);

int	cmd_echo(char **argv)
{
	int		i;
	bool	option_n;

	option_n = exist_n_option(argv);
	if (option_n == true)
		i = 2;
	else
		i = 1;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (option_n == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return(EXIT_SUCCESS);
}

static bool	exist_n_option(char **argv)
{
	if (argv[1] && ft_strncmp(argv[1], "-n", 3) == 0)
		return (true);
	return (false);
}
