#include "minishell.h"

static void	filename_heredoc(t_minishell *shell);
void	heredoc(t_minishell *shell, t_cmd_data *cmd);
int	heredoc_2_array(t_minishell *shell, char **redir, char **file);

void	heredoc(t_minishell *shell, t_cmd_data *cmd)
{
	char	*file;
	int		i;
	int		pid;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (ft_strncmp (cmd->redir[i], "<<" , 2) == 0)
		{
			file = filename_heredoc(shell);
			pid = fork();
			if (pid == -1)
				error_p(shell, "fork", FATAL, 1);
			signal_toggle(IGNORE);
			if (pid == 0)
				heredoc_child(shell, cmd, file, i);
			waitpid(pid, &shell->exit_status, 0);
			signal_toggle(INTERACTIVE);
			if (heredoc_2_array(shell, &cmd->redir[i], &file))
				return ;
			shell->heredoc_index++;
		}
		i++;
	}
}

static void	filename_heredoc(t_minishell *shell)
{
	char	*file;
	char	*tmp;

	tmp = ft_itoa(shell->heredoc_index);
	if (!tmp)
		error(shell, MALLOC_ERR, FATAL, 1);
	file = ft_strjoin("/tmp/heredoc", tmp);
	free(tmp);
	if (!file)
		error(shell, MALLOC_ERR, FATAL, 1);
	return (file);
}

int	heredoc_2_array(t_minishell *shell, char **redir, char **file)
{
	if (shell->exit_status != 0)
	{
		shell->status = ERROR;
		shell->exit_status = 1;
		free(*file);
		return (1);
	}
	free(*redir);
	*redir = ft_strjoin("< ", *file);
	free(*file);
	if (!*redir)
		error(shell, ERR_MALLOC, FATAL, 1);
	return (0);
}