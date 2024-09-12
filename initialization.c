/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:42:00 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/11 23:14:23 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	promt_init(t_minishell *shell)
{
	shell->pipes_allocated = 0;
	shell->pipe = NULL;
	shell->pid_allocated = 0;
	shell->pid = NULL;
	shell->cmd_count = 0;
	shell->cmd_tree = NULL;
	shell->heredoc_index = 0;
	shell->paths = NULL;
	shell->parent_redir = 0;
}

static void	cmd_init(t_cmd_data *cmd)
{
	cmd->arg_count = 0;
	cmd->args = NULL;
	cmd->cmd = NULL;
	cmd->index = 0;
	cmd->infile = -2;
	cmd->out = -2;
	cmd->line = NULL;
	cmd->redir = NULL;
	cmd->redir_count = 0;
}

void	tree_init(t_minishell *shell)
{
	int	i;

	i = 0;
	shell->cmd_tree = ((t_cmd_data *)malloc(sizeof(t_cmd_data)
				* (shell->cmd_count + 1)));
	if (!shell->cmd_count)
	{
		error(shell, ERR_MALLOC, FATAL, 1);
	}
	while (i < shell->cmd_count)
	{
		cmd_init(&shell->cmd_tree[i]);
		i++;
	}
	shell->cmd_tree[i].line = NULL;
	shell->pid = (int *)malloc(sizeof(int) * shell->cmd_count);
	if (!shell->pid)
		error(shell, ERR_MALLOC, FATAL, 1);
	shell->pid_allocated = 1;
	paths(shell, shell->env);
}

void	init_t_parse(t_parsed_data *parsed)
{
	parsed->i = 0;
	parsed->k = 0;
	parsed->inside_singles = 0;
	parsed->inside_doubles = 0;
	parsed->in_quotes = 0;
	parsed->quote = 0;
}

void	shell_init(t_minishell *shell, char **envp)
{
	shell->line = NULL;
	shell->status = RUNNING;
	shell->cmd_count = 0;
	shell->cmd_tree = NULL;
	shell->pid = NULL;
	shell->pid_allocated = 0;
	shell->pipe = NULL;
	shell->pipes_allocated = 0;
	shell->paths = NULL;
	shell->exit_status = 0;
	shell->cmd_count = 0;
	shell->paths = NULL;
	shell->old_pwd = NULL;
	shell->pwd = NULL;
	shell->env = array_copy(shell, envp);
	shell->pwd = getcwd(NULL, 0);
	if (!shell->pwd)
		ft_putendl_fd(ERR_CWD, 2);
	if (isatty(STDIN_FILENO))
	{
		shlvl_increment(shell);
		rm_fr_array(shell->env, "OLDPWD");
		shell->env = add_to_array(shell, shell->env, "OLDPWD", 0);
	}
}
