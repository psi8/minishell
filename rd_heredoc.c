/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:33:35 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/15 22:30:27 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	heredoc_prompt(t_cmd_data *cmd, char *file, char *delimiter)
{
	int		fd;
	char	*user_input;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	user_input = NULL;
	while (true)
	{
		signals_wait_cmd();
		user_input = readline("heredoc> ");
		signals_run_cmd();
		if (prompt_heredoc_exit(&user_input, delimiter) == true)
			break ;
		ft_putendl_fd(user_input, fd);
		free_ptr(user_input);
	}
	close(fd);
	free_ptr(user_input);
	return (true);
}

static t_bool	prompt_heredoc_exit(char **user_in, char *delimiter)
{
	if (*user_in == NULL)
	{
		error_msg_cmd("here-doc", "end-of-file: expected",
			delimiter, true);
		return (true);
	}
	if (ft_strncmp(*user_in, delimiter,
			ft_strlen(delimiter)) == 0)
	{
		return (true);
	}
	return (false);
}


static char	*heredoc_filename(t_minishell *shell)
{
	char	*file;
	char	*tmp;

	tmp = ft_itoa(shell->heredoc_index);
	if (!tmp)
		error(shell, MALLOC_ERR, FATAL, 1);
	file = ft_strjoin("/tmp/.heredoc", tmp);
	free(tmp);
	if (!file)
		error(shell, MALLOC_ERR, FATAL, 1);
	return (file);
}

int	add_heredoc_to_array(t_minishell *shell, char **redir, char **file)
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
		error(shell, MALLOC_ERR, FATAL, 1);
	return (0);
}

void	heredoc(t_minishell *shell, t_cmd_data *cmd)
{
	int		pid;
	int		i;
	char	*file;
	char *delimiter;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (ft_strncmp(cmd->redir[i], "<<", 2) == 0)
		{
			file = heredoc_filename(shell);
			delimiter = cmd->redir[i] + 2;
			heredoc_prompt(cmd, file, delimiter, i);
			if (add_heredoc_to_array(shell, &cmd->redir[i], &file))
				return ;
			shell->heredoc_index++;
		}
		i++;
	}
}
