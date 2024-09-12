/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:28:51 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/12 20:36:32 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		signals_wait_cmd(void);
void		signals_run_cmd(void);
static void	reset_prompt(int signo);
static void	new_line(int signo);

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

static void	reset_prompt(int signo)
{
	g_sigint_received = 128 + signo;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	new_line(int signo)
{
	g_sigint_received = 128 + signo;
	rl_on_new_line();
}
