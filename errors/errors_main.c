#include "minishell.h"

int	error(t_minishell *shell, char *msg, t_exit_status status, int code)
{
	char	*err_msg;

	if(!msg)
		free_and_exit(shell, 1);
	if (shell->parent_redir)
		//restore_std(shell);
	err_msg = make_err_msg(msg);
	if (!err_msg)
		free_and_exit(shell, 1);
	else
	{
		write(2, err_msg, ft_strlen(err_msg));
		free(err_msg);
	}
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
		free_and_exit(shell, code);
	return (1);
}