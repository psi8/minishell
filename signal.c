
/*
*   Pavel! You are able to delete all this function and file. Needs only for test.
*
*
*/

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

void	toggle_signal(t_signal mode)
{
	if (mode == DEFAULT)
	{
		toggle_caret(1);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (mode == HANDLER)
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
	else if (mode == NO_SIGNALS)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
