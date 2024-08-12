/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:49:38 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/10 17:49:38 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exec_local_bin(t_data *data, t_commands *cmds, int num_cmd);
static int	exec_path_var_bin(t_data *data, t_commands *cmds, int num_cmd);
static int	wait_child(t_commands *cmds);

int	exec_main(t_minishell shell)
{
	int	status_code;
	int	g_status_code;
	int i;

	i = -1;
	status_code = 0;
	while (++i < shell->cmd_count)
	{
		if (shell->cmd_tree[i].args[0] && is_builtin_without_output(&shell->cmd_tree[i]))
			exec_builtin_without_output(shell, &shell->cmd_tree[i]);
		else
		{
			status_code = exec_child(data, cmds, cmds->num_exec);
			g_status_code = wait_child(cmds);
			if (status_code != 0)
				g_status_code = status_code;
			if (cmds->num_exec < cmds->num_cmds)
				verify_operators(data, cmds, cmds->num_exec);
		}
	}
	return (g_status_code);
}

static int	wait_child(t_commands *cmds)
{
	int	i;
	int	status;
	int	save_status;

	close_exec_pipe_fds(cmds);
	i = -1;
	status = 0;
	save_status = 0;
	while (++i < cmds->num_exec - 1)
		waitpid(cmds->pid[i], NULL, 0);
	waitpid(cmds->pid[i], &save_status, 0);
	if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else
		status = cmds->exit_value;
	return (status);
}

int	execute_cmd(t_data *data, t_commands *cmds, int num_cmd)
{
	int	status_code;

	if (cmds->operators[0])
		set_pipe_fds(cmds, num_cmd);
	if (is_redirection_command(cmds, num_cmd)
		&& check_in_out_file(cmds->io, cmds, true) == false)
		exit_shell(data, EXIT_FAILURE);
	redirect_io(cmds->io, num_cmd);
	close_fds(cmds, false);
	if (is_builtin(cmds->cmd[num_cmd].args[0]))
		status_code = call_builtin(data, cmds, num_cmd);
	else
	{
		if (ft_strchr(cmds->cmd[num_cmd].args[0], '/') == NULL)
		{
			status_code = exec_path_var_bin(data, cmds, num_cmd);
			if (status_code != CMD_NOT_FOUND)
				free_exit_cmd(data, cmds, status_code);
		}
		status_code = exec_local_bin(data, cmds, num_cmd);
	}
	free_cmds(cmds);
	exit_shell(data, status_code);
	return (status_code);
}

static int	exec_path_var_bin(t_data *data, t_commands *cmds, int num_cmd)
{
	cmds->cmd[num_cmd].path = get_cmd_path(cmds, num_cmd);
	if (!cmds->cmd[num_cmd].path)
		return (CMD_NOT_FOUND);
	if (execve(cmds->cmd[num_cmd].path, cmds->cmd[num_cmd].args, data->env)
		== -1)
		error_msg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

static int	exec_local_bin(t_data *data, t_commands *cmds, int num_cmd)
{
	int	result_code;

	result_code = validate_cmd_not_found(data, cmds->cmd[num_cmd].args[0]);
	if (result_code != 0)
		return (result_code);
	if (execve(cmds->cmd[num_cmd].args[0], cmds->cmd[num_cmd].args, data->env)
		== -1)
		return (error_msg_cmd("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

bool	input_is_dir(char *cmd)
{
	struct stat	stat_buf;

	stat(cmd, &stat_buf);
	return (S_ISDIR(stat_buf.st_mode));
}

int	validate_cmd_not_found(t_data *data, char *cmd)
{
	if (ft_strchr(cmd, '/') == NULL
		&& get_env_var_index(data->env, "PATH") != -1)
		return (error_msg_cmd(cmd, NULL, "command not found", CMD_NOT_FOUND));
	if (access(cmd, F_OK) != 0)
		return (error_msg_cmd(cmd, NULL, strerror(errno), CMD_NOT_FOUND));
	else if (input_is_dir(cmd))
		return (error_msg_cmd(cmd, NULL, "Is a directory", CMD_NOT_EXEC));
	else if (access(cmd, X_OK) != 0)
		return (error_msg_cmd(cmd, NULL, strerror(errno), CMD_NOT_EXEC));
	return (0);
}

void	free_exit_cmd(t_data *data, t_commands *cmds, int status_code)
{
	close_fds(cmds, true);
	free_cmds(cmds);
	exit_shell(data, status_code);
}
