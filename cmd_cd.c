/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:41:57 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/03 14:41:57 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_dir(t_minishell *shell, char *path);
static void	update_work_dir_var(t_minishell *shell, char *path);

int	cmd_cd(t_minishell *shell, char **argv)
{
	char	*path;

	if (!argv[1] || ft_isspace(argv[1][0]) || argv[1][0] == '\0'
		|| ft_strncmp(argv[1], "--", 3) == 0 || ft_strncmp(argv[1], " ", 2) == 0)
	{
		path = ft_get_env(shell->hashmap, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (print_err_msg("cd: HOME not set"));
		return (change_dir(shell, path));
	}
	else if (argv[2])
		return (print_err_msg("cd: too many arguments"));
	else if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		path = ft_get_env(shell->hashmap, "OLDPWD");
		if (!path)
			return (print_err_msg("cd: OLDPWD not set"));
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
		return (perror_err_msg("cd", path));
	getcwd(buff, MAX_PATH);
	path_pwd = ft_strdup(buff);
	update_work_dir_var(shell, path_pwd);
	return (EXIT_SUCCESS);
}

static void	update_work_dir_var(t_minishell *shell, char *path)
{
	ft_add_env_hash(shell->hashmap, "OLDPWD", ft_get_env(shell->hashmap, "PWD"));
	ft_add_env_hash(shell->hashmap, "PWD", path);
	if (shell->oldpwd)
		free(shell->oldpwd);
	shell->oldpwd = ft_strdup(shell->pwd);
	if (shell->pwd)
		free(shell->pwd);
	shell->pwd = ft_strdup(path);
	free(path);
}
