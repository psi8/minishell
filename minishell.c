/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:55:40 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/13 16:32:51 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//test

volatile sig_atomic_t	g_sigint_received = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	if (!argv || argc < 1)
		return (0);
	shell_init(&shell, envp);
	signal_toggle(INTERACTIVE);
	while (shell.status == RUNNING)
	{
		shell.line = readline("my_minishell: ");
		if (shell.line == NULL)
			terminate_shell(&shell);
		if (*shell.line)
		{
			add_history(shell.line);
			line_parse(&shell);
			process_execution(&shell);
			all_free(&shell);
		}
		else
			free(shell.line);
		shell.status = RUNNING;
	}
	terminate_shell(&shell);
}
