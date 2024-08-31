/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:39:11 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/31 20:23:55 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//test

volatile sig_atomic_t	g_sigint_received = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell		shell;
	
	(void)argc;
	(void)argv;

/*	int test = test_main(envp); //debug builtin and pipe
	if (test != 0)
		return (test);
	else
		return (0);
	//debug fiinish
*/	
	if (!argv || argc < 1)
		return (0);
	shell_init(&shell, envp);
	signal_toggle(INTERACTIVE);
	while(shell.status == RUNNING)
	{
		shell.line = readline("my_minishell: ");
		if (shell.line == NULL)
			exit_shell(&shell);
		if(*shell.line)
		{
			add_history(shell.line);
			line_parse(&shell);
		}
	}
}

/* void	signal_intercept(int status)
{
	if (status == DEFAULT)
		init_intercept(SIG_DFL, SIG_DFL);
	else if (status == INTERACTIVE)
		init_intercept(int_sig_handler, SIG_IGN);
	else if (status == HEREDOC)
		init_intercept(SIG_DFL, SIG_IGN);
	else if (status == IGNORE)
		init_intercept(SIG_IGN, SIG_IGN);
}

static void	interceptor_init(void (*hand_one)(int), void (*hand_two)(int))
{
	struct sigaction	sa;
	struct sigaction	sq;

	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&sq, 0, sizeof(sq));
	sa.sa_handler = hand_one;
	sq.sa_handler = hand_two;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&sq.sa_mask);
	sa.sa_flags = SA_RESTART;
	sq.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sq, NULL);
}

void	int_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint_received = signum;
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_printf("\033[1A");
		write(1, "\n", 1);
	}
}

void	signal_set(int status)
{
	struct termios	term;

	status += status;
	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	if (status)
		term.c_lflag |= ECHOCTL;
	else if (!status)
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
*/
