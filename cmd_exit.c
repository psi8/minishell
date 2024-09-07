/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:49:13 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/07 17:50:05 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * handle_exit_error - Handles the error message when a non-numeric exit argument is provided.
 * @sh: Pointer to the main minishell structure.
 * @str: The string that caused the error.
 */
static void handle_exit_error(t_minishell *sh, char *str)
{
    char *error_msg;
    char *tmp;

    tmp = ft_strjoin("minishell: exit: ", str);
    if (!tmp)
        error(sh, ERR_MALLOC, FATAL, 1);
    error_msg = ft_strjoin(tmp, ": numeric argument required\n");
    free(tmp);
    if (!error_msg)
        error(sh, ERR_MALLOC, FATAL, 1);
    write(2, error_msg, ft_strlen(error_msg));
    free(error_msg);
    free_and_exit(sh, 2);  // Updated function name
}

/**
 * is_non_numeric - Checks if the provided argument is non-numeric.
 * @sh: Pointer to the main minishell structure.
 * @str: The string to check.
 * @return: 1 if non-numeric, 0 otherwise.
 */
static t_bool is_non_numeric(t_minishell *sh, char *str)
{
    int index;

    index = 0;
    if (str[index] == '-' || str[index] == '+')
        index++;
    while (str[index])
    {
        if (!ft_isdigit(str[index]))
            handle_exit_error(sh, str);
        index++;
    }
    return (false);
}

/**
 * parse_exit_value - Converts the exit string to an integer and handles errors.
 * @sh: Pointer to the main minishell structure.
 * @str: The string representing the exit value.
 * @return: The converted integer.
 */
static int parse_exit_value(t_minishell *sh, char *str)
{
    int num;

    if (!ft_strncmp(str, "9223372036854775807", 19))
        return (255);
    if (!ft_strncmp(str, "-9223372036854775808", 19))
        return (0);
    num = ft_atoi(str);
    if (num == -1 && ft_strncmp(str, "-1", 2))
        handle_exit_error(sh, str);
    if (num == 0 && ft_strncmp(str, "0", 1))
        handle_exit_error(sh, str);
    return (num);
}

/**
 * execute_exit - Handles the `exit` command in minishell.
 * @sh: Pointer to the main minishell structure.
 * @cmd_data: Pointer to the command-specific data.
 */
void cmd_exit(t_minishell *sh, t_cmd_data *cmd_data)
{
    if (sh->parent_redir)
        restore_std(sh);
    if (isatty(STDIN_FILENO) && sh->cmd_count == 1)
        write(2, "exit\n", 5);
    if (cmd_data->args[1])
    {
        if (!is_non_numeric(sh, cmd_data->args[1]))
            sh->exit_status = parse_exit_value(sh, cmd_data->args[1]);
        if (cmd_data->args[2])
        {
            write(2, "minishell: exit: too many arguments\n", 37);
            sh->exit_status = 1;
            return;
        }
    }
    else
        sh->exit_status = WEXITSTATUS(sh->exit_status);
    free_and_exit(sh, sh->exit_status);  // Updated function name
}
