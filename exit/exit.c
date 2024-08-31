#include "../minishell.h"

void	exit_shell(t_minishell *shell)
{
	if (isatty(STDIN_FILENO))
	{
		ft_putstr_fd("EXIT", 2);
		ft_putchar_fd('\n', 2);
	}
	array_free(&shell->env);
	all_free(shell);
	signal_toggle(DEFAULT);
	exit(shell->exit_status);
}

void	free_and_exit(t_minishell *shell, int status)
{
	if (shell->parent_redir)
		restore_std(shell);
	all_free(shell);
	array_free(&shell->env);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->old_pwd)
		free(shell->old_pwd);
	signal_toggle(DEFAULT);
	exit(status);
}
