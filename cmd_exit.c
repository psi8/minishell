/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:49:13 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/25 11:32:07 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_code_handler(char *arg, t_bool *error);

int	cmd_exit(t_minishell *shell, char **argv)
{
	int		exit_code;
	t_bool	error;

	error = false;
	if (!argv[1])
		exit_code = shell->exit_status;
	else
	{
		exit_code = exit_code_handler(argv[1], &error);
		if (error)
			exit_code = error_msg_cmd("exit", argv[1], "numeric argument required", STDERR_FILENO);
		else if (argv[2])
		{
			shell->exit_status = 1;
			return (error_msg_cmd("exit", NULL, "too many arguments", EXIT_FAILURE));
		}
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_and_exit(shell, exit_code);
	return (STDERR_FILENO);
}

static int	exit_code_handler(char *arg, t_bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (0);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_ato_long(arg, error);
	return (i % 256);
}
