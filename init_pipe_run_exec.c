/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe_run_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:02:06 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/02 22:58:03 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void process_execution(t_minishell *sh)
{
    if (sh->status == ERROR)
        return;

    if (sh->cmd_count == 1 && is_builtin(&sh->cmd_tree[0].cmd))
    {
        if (sh->cmd_tree[0].redir_count > 0)
        {
            sh->parent_redir = 1;
            sh->std_in = dup(STDIN_FILENO);
            sh->std_out = dup(STDOUT_FILENO);
            redirect_to_io(sh, &sh->cmd_tree[0], ERROR);
        }
        if (sh->status != ERROR)
            run_builtin(sh, &sh->cmd_tree[0]);

        if (sh->parent_redir)
            restore_std(sh);
        
        return;
    }

    if (sh->cmd_count > 1)
        open_pipes(sh);

    do_fork(sh);
}

