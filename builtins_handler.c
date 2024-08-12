/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:36:23 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/12 20:07:39 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin_without_output(t_cmd_data *cmd)
{
	if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0 && cmd->args[0])
		return (true);
	else
		return (false);
}

bool	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	else
		return (false);
}

int	call_builtin(t_minishell *shell, t_cmd_data *cmd)
{
	int	cmd_code;

	cmd_code = 0;
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		cmd_code = cmd_echo(cmd->args);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		cmd_code = cmd_exit(shell, argv);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		cmd_code = cmd_pwd();
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		cmd_code = cmd_env(shell);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		cmd_code = cmd_cd(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		cmd_code = cmd_unset(shell, argv);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		cmd_code = cmd_export(shell, argv);
	else
		exit(EXIT_SUCCESS);
	return (cmd_code);
}
