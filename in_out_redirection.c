/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:58:01 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/07 18:11:45 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void terminate_pipes(t_minishell *sh);

/**
 * duplicate_and_close - Duplicates a file descriptor to another target and closes the original.
 * @file_descriptor: The original file descriptor to duplicate.
 * @file_descriptor_target: The target file descriptor to duplicate to.
 */
static void duplicate_and_close(int file_descriptor, int file_descriptor_target)
{
    if (file_descriptor == -1)
        return;
    dup2(file_descriptor, file_descriptor_target);
    close(file_descriptor);
}

/**
 * redirect_to_pipe - Redirects input/output to the appropriate pipes based on the command's position.
 * @sh: Pointer to the main minishell structure.
 * @cmd_data: Pointer to the command-specific data.
 */
void redirect_to_pipe(t_minishell *sh, t_cmd_data *cmd_data)
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
 * unclear_redirect - Checks for and handles ambiguous redirects, providing error messages if found.
 * @sh: Pointer to the main minishell structure.
 * @file_path: The file path to check for ambiguous redirects.
 * @exit_mode: The mode determining how to handle errors.
 * @return: 1 if ambiguous redirect found and handled, 0 otherwise.
 */
static int unclear_redirect(t_minishell *sh, char **file_path, t_exit_status exit_mode)
{
    char    *temporary_str;
    char    *error_message;
    int     iterator;

    iterator = 2;
    if (!strchr(*file_path, '$'))
        return (0);
    temporary_str = ft_strdup(*file_path + 2);
    if (!temporary_str)
        return (error(sh, ERR_MALLOC, FATAL, 1));
    expand(sh, file_path);
    while (file_path[0][iterator] && file_path[0][iterator] != ' ')
        iterator++;
    if (iterator == 2 || file_path[0][iterator] == ' ')
    {
        error_message = ft_strjoin(temporary_str, ERR_UNCLEAR_REDIRECTION);
        free(temporary_str);
        error(sh, error_message, exit_mode, 1);
        free(error_message);
        return (1);
    }
    free(temporary_str);
    return (0);
}


void redirect_to_io(t_minishell *sh, t_cmd_data *cmd, t_exit_status exit_mode)
{
    int index;

    index = -1;
    while (cmd->redir[++index] && sh->status != ERROR)
    {
        if (unclear_redirect(sh, &cmd->redir[index], exit_mode))
            return;
        if (ft_strncmp(&cmd->redir[index][0], "< ", 2) == 0)
        {
            cmd->infile = open(cmd->redir[index] + 2, O_RDONLY);
            duplicate_and_close(cmd->infile, STDIN_FILENO);
        }
        else if (ft_strncmp(&cmd->redir[index][0], "> ", 2) == 0)
        {
            cmd->out = open(cmd->redir[index] + 2, O_CREAT | O_RDWR | O_TRUNC, 0644);
            duplicate_and_close(cmd->out, STDOUT_FILENO);
        }
        else if (ft_strncmp(&cmd->redir[index][0], ">>", 2) == 0)
        {
            cmd->out = open(cmd->redir[index] + 2, O_CREAT | O_APPEND | O_RDWR, 0644);
            duplicate_and_close(cmd->out, STDOUT_FILENO);
        }
        if (cmd->infile == -1 || cmd->out == -1)
            error_p(sh, cmd->redir[index] + 2, exit_mode, 1);
    }
}

/**
 * terminate_pipes - Closes all pipe file descriptors in the minishell instance.
 * @sh: Pointer to the main minishell structure.
 */
void terminate_pipes(t_minishell *sh)
{
    int pipe_index;

    pipe_index = 0;
    while (pipe_index < sh->cmd_count)
    {
        close(sh->pipe[pipe_index][0]);
        close(sh->pipe[pipe_index][1]);
        pipe_index++;
    }
}
