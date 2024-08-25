#include "minishell.h"

static void	filename_heredoc(t_minishell *shell);
void	heredoc(t_minishell *shell, t_cmd_data *cmd);

void	heredoc(t_minishell *shell, t_cmd_data *cmd)
{
	int		pid;
	int		i;
	char	*file;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (ft_strncmp (cmd->redir[i], "<<" , 2) == 0)
		{
			file = filename_heredoc(shell);
			pid = fork()
		}
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