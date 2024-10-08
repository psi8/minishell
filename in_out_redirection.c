/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:38:48 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/12 20:20:27 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate_pipes(t_minishell *sh);

/**
 * duplicate_and_close - Duplicates a file descriptor to another target and 
 * closes the original.
 * @file_descriptor: The original file descriptor to duplicate.
 * @file_descriptor_target: The target file descriptor to duplicate to.
 */
static void	duplicate_and_close(int file_descriptor, int file_descriptor_target)
{
	if (file_descriptor == -1)
		return ;
	dup2(file_descriptor, file_descriptor_target);
	close(file_descriptor);
}

/**
 * redirect_to_pipe - Redirects input/output to the appropriate pipes based on
 * the command's position.
 * @sh: Pointer to the main minishell structure.
 * @cmd_data: Pointer to the command-specific data.
 */
void	redirect_to_pipe(t_minishell *sh, t_cmd_data *cmd_data)
{
	if (cmd_data->index == 0)
	{
		dup2(sh->pipe[cmd_data->index][1], STDOUT_FILENO);
		terminate_pipes(sh);
	}
	else if (cmd_data->index < sh->cmd_count - 1)
	{
		dup2(sh->pipe[cmd_data->index][1], STDOUT_FILENO);
		dup2(sh->pipe[cmd_data->index - 1][0], STDIN_FILENO);
		terminate_pipes(sh);
	}
	else if (cmd_data->index == sh->cmd_count - 1)
	{
		dup2(sh->pipe[cmd_data->index - 1][0], STDIN_FILENO);
		terminate_pipes(sh);
	}
}

/**
 * unclear_redirect - Checks for and handles ambiguous redirects, providing error
 * messages if found.
 * @sh: Pointer to the main minishell structure.
 * @file_path: The file path to check for ambiguous redirects.
 * @ex_mode: The mode determining how to handle errors.
 * @return: 1 if ambiguous redirect found and handled, 0 otherwise.
 */
static int	unclear_redirect(t_minishell *sh, char **f_p, t_exit_status ex_md)
{
	char	*temporary_str;
	char	*error_message;
	int		iterator;

	iterator = 2;
	if (!strchr(*f_p, '$'))
		return (0);
	temporary_str = ft_strdup(*f_p + 2);
	if (!temporary_str)
		return (error(sh, ERR_MALLOC, FATAL, 1));
	expand(sh, f_p);
	while (f_p[0][iterator] && f_p[0][iterator] != ' ')
		iterator++;
	if (iterator == 2 || f_p[0][iterator] == ' ')
	{
		error_message = ft_strjoin(temporary_str, ERR_UNCLEAR_REDIRECTION);
		free(temporary_str);
		error(sh, error_message, ex_md, 1);
		free(error_message);
		return (1);
	}
	free(temporary_str);
	return (0);
}

void	redirect_to_io(t_minishell *sh, t_cmd_data *c, t_exit_status ex_mode)
{
	int	i;

	i = -1;
	while (c->redir[++i] && sh->status != ERROR)
	{
		if (unclear_redirect(sh, &c->redir[i], ex_mode))
			return ;
		if (ft_strncmp(&c->redir[i][0], "< ", 2) == 0)
		{
			c->infile = open(c->redir[i] + 2, O_RDONLY);
			duplicate_and_close(c->infile, STDIN_FILENO);
		}
		else if (ft_strncmp(&c->redir[i][0], "> ", 2) == 0)
		{
			c->out = open(c->redir[i] + 2, O_CREAT | O_RDWR | O_TRUNC, 0644);
			duplicate_and_close(c->out, STDOUT_FILENO);
		}
		else if (ft_strncmp(&c->redir[i][0], ">>", 2) == 0)
		{
			c->out = open(c->redir[i] + 2, O_CREAT | O_APPEND | O_RDWR, 0644);
			duplicate_and_close(c->out, STDOUT_FILENO);
		}
		if (c->infile == -1 || c->out == -1)
			error_p(sh, c->redir[i] + 2, ex_mode, 1);
	}
}

/**
 * terminate_pipes - Closes all pipe file descriptors in the minishell instance.
 * @sh: Pointer to the main minishell structure.
 */
void	terminate_pipes(t_minishell *sh)
{
	int	pipe_index;

	pipe_index = 0;
	while (pipe_index < sh->cmd_count)
	{
		close(sh->pipe[pipe_index][0]);
		close(sh->pipe[pipe_index][1]);
		pipe_index++;
	}
}
