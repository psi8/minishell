
/*
*   Pavel! You are able to delete all this function and file. Needs only for test.
*
*
*/

#include "minishell.h"

static void	new_line(int signal);
static void	reset_prompt(int signo);
static void	toggle_caret(int is_on);
static void	signal_handler(int signal);
static void	heredoc_handler(int signal);

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

void	toggle_signal(t_signals mode)
{
	if (mode == DEFAULT)
	{
		toggle_caret(1);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (mode == INTERACTIVE)
	{
		toggle_caret(0);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_handler);
	}
	else if (mode == IGNORE)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}

static void	toggle_caret(int is_on)
{
	struct termios	new_attr;

	tcgetattr(STDIN_FILENO, &new_attr);
	if (!is_on)
		new_attr.c_lflag &= ~ECHOCTL;
	else
		new_attr.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
	}
}

static void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}