/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:12:42 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/09/12 20:55:28 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	caret_toggle(int on);
static void	sig_hand(int signal);
static void	heredoc_hand(int signal);
void		signal_toggle(t_signals status);

static void	caret_toggle(int on)
{
	struct termios	new_att;

	tcgetattr (STDIN_FILENO, &new_att);
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
		signal (SIGQUIT, SIG_IGN);
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
