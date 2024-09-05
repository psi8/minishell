/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:36:23 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/02 22:48:51 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_builtin_without_output(t_cmd_data *cmd)
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

t_bool	is_builtin(char *cmd)
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

t_bool	call_builtin(t_minishell *shell, t_cmd_data *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		cmd_echo(cmd->args);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		cmd_exit(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		cmd_pwd();
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		cmd_env(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		cmd_cd(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		cmd_unset(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		cmd_export(shell, cmd->args);
	else
		return(false);
	return (true);
}
