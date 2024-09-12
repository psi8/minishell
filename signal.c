/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:12:42 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/12 20:16:52 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*   Pavel! You are able to delete all this function and file. Needs only for test.
*
*
*/

#include "minishell.h"

static void	new_line(int signal);
static void	reset_prompt(int signo);
void	signal_toggle(t_signals status);
static void	caret_toggle(int on);
static void	sig_hand(int signal);
static void	heredoc_hand(int signal);

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
	g_sigint_received = 128 + signo;
	rl_on_new_line();
}

static void	reset_prompt(int signo)
{
	g_sigint_received = 128 + signo;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_toggle(t_signals status)
{
	if (status == DEFAULT)
	{
		caret_toggle(1);
		signal (SIGQUIT, SIG_DFL);
		signal (SIGINT, SIG_DFL);
	}
	else if (status == INTERACTIVE)
	{
		caret_toggle(0);
		signal(SIGQUIT,SIG_IGN);
		signal (SIGINT, sig_hand);
	}
	else if (status == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_hand);
	}
	else if (status == IGNORE)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}

static void	caret_toggle(int on)
{
	struct termios	new_att;
	tcgetattr(STDIN_FILENO, &new_att);
	if (!on)
		new_att.c_cflag &= ~ECHOCTL;
	else
		new_att.c_cflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_att);
}

static void	sig_hand(int signal)
{
	if (signal == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	heredoc_hand(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}