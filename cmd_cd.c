/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:41:57 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/06 23:23:31 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_dir(t_minishell *shell, char *path);
static void	update_work_dir_var(t_minishell *shell, char *path);
static void	cd_error(t_minishell *shell, char *path);

int	cmd_cd(t_minishell *shell, char **argv)
{
	char	*path;

	if (!argv[1] || ft_isspace(argv[1][0]) || argv[1][0] == '\0'
		|| ft_strncmp(argv[1], "--", 3) == 0 || ft_strncmp(argv[1], " ", 2) == 0)
	{
		path = ft_get_env(shell, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (error(shell, "cd: HOME not set", ERROR, 1));
		return (change_dir(shell, path));
	}
	else if (argv[2])
		return (error(shell,  "cd: too many arguments", ERROR, 1));
	else if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		path = ft_get_env(shell, "OLDPWD");
		if (!path)
			return (error(shell, "cd: OLDPWD not set", ERROR, 1));
		return (change_dir(shell, path));
	}
	else
		return (change_dir(shell, argv[1]));
}

static int	change_dir(t_minishell *shell, char *path)
{
	char	*path_pwd;
	char	buff[MAX_PATH];

	if (chdir(path) != 0)
	{
		cd_error(shell, path);
		return (1);
	}
	getcwd(buff, MAX_PATH);
	path_pwd = ft_strdup(buff);
	update_work_dir_var(shell, path_pwd);
	return (EXIT_SUCCESS);
}

static void	update_work_dir_var(t_minishell *shell, char *path)
{
//	ft_update_pwd(shell);
//	ft_add_env_hash(shell->hashmap, "PWD", path);
	if (shell->old_pwd)
		free(shell->old_pwd);
	shell->old_pwd = ft_strdup(shell->pwd);
	if (shell->pwd)
		free(shell->pwd);
	shell->pwd = ft_strdup(path);
	free(path);
}

static void	cd_error(t_minishell *shell, char *path)
{
	char	*error_msg;

	error_msg = ft_strjoin("cd: ", path);
	if (!error_msg)
	{
		free(error_msg);
		error(shell, ERR_MALLOC, FATAL, 1);
	}
	error_p(shell, error_msg, ERROR, 1);
	free(error_msg);
}
