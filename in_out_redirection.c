/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:58:01 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/31 19:12:42 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_minishell *shell);

static void	dup_and_close(int file, int fd)
{
	if (file == -1)
		return ;
	dup2(file, fd);
	close(file);
}

void	redir_to_pipe(t_minishell *shell, t_cmd_data *cmd_vars)
{
	if (cmd_vars->index == 0)
	{
		dup2(shell->pipe[cmd_vars->index][1], STDOUT_FILENO);
		close_pipes(shell);
	}
	else if (cmd_vars->index < shell->cmd_count - 1)
	{
		dup2(shell->pipe[cmd_vars->index][1], STDOUT_FILENO);
		dup2(shell->pipe[cmd_vars->index - 1][0], STDIN_FILENO);
		close_pipes(shell);
	}
	else if (cmd_vars->index == shell->cmd_count - 1)
	{
		dup2(shell->pipe[cmd_vars->index - 1][0], STDIN_FILENO);
		close_pipes(shell);
	}
}

static int	ambiguous_redirect(t_minishell *shell, char **file, t_exit_status mode)
{
	char	*tmp;
	char	*msg;
	int		i;

	i = 2;
	if (!strchr(*file, '$'))
		return (0);
	tmp = ft_strdup(*file + 2);
	if (!tmp)
		return (error(shell, ERR_MALLOC, FATAL, 1));
//	expand(shell, file);
	while (file[0][i] && file[0][i] != ' ')
		i++;
	if (i == 2 || file[0][i] == ' ')
	{
		msg = ft_strjoin(tmp, ": ambiguous redirect");
		free(tmp);
		error(shell, msg, mode, 1);
		free(msg);
		return (1);
	}
	free(tmp);
	return (0);
}

void	redir_to_file(t_minishell *shell, t_cmd_data *c, t_exit_status mode)
{
	int	i;

	i = -1;
	while (c->redir[++i] && shell->status != ERROR)
	{
		if (ambiguous_redirect(shell, &c->redir[i], mode))
			return ;
		if (ft_strncmp(&c->redir[i][0], "< ", 2) == 0)
		{
			c->infile = open(c->redir[i] + 2, O_RDONLY);
			dup_and_close(c->infile, STDIN_FILENO);
		}
		else if (ft_strncmp(&c->redir[i][0], "> ", 2) == 0)
		{
			c->out = open(c->redir[i] + 2, O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup_and_close(c->out, STDOUT_FILENO);
		}
		else if (ft_strncmp(&c->redir[i][0], ">>", 2) == 0)
		{
			c->out = open(c->redir[i] + 2, O_CREAT | O_APPEND | O_RDWR, 0644);
			dup_and_close(c->out, STDOUT_FILENO);
		}
		if (c->infile == -1 || c->out == -1)
			error(shell, c->redir[i] + 2, mode, 1);
	}
}

void	close_pipes(t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		close(shell->pipe[i][0]);
		close(shell->pipe[i][1]);
		i++;
	}
}
