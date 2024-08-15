/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:12:42 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/15 22:15:16 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

static void	new_line(int signal);
static void	reset_prompt(int signo);

void	signals_wait_cmd(void)
{
	signal(SIGINT, reset_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_run_cmd(void)
{
	signal(SIGINT, new_line);
	signal(SIGQUIT, new_line);
}

static void	new_line(int signo)
{
	g_sigint_receive = 128 + signo;
	rl_on_new_line();
}

static void	reset_prompt(int signo)
{
	g_sigint_receive = 128 + signo;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
