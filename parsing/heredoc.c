/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:50:50 by psitkin           #+#    #+#             */
/*   Updated: 2024/09/13 16:02:49 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*filename_heredoc(t_minishell *shell);
void		heredoc(t_minishell *shell, t_cmd_data *cmd);
int			heredoc_2_array(t_minishell *shell, char **redir, char **file);
void		child_heredoc(t_minishell *sh, t_cmd_data *cmd, char *file, int i);

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	heredoc(t_minishell *shell, t_cmd_data *cmd)
{
	char	*file;
	int		i;
	int		pid;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (ft_strncmp (cmd->redir[i], "<<", 2) == 0)
		{
			file = filename_heredoc(shell);
			pid = fork();
			if (pid == -1)
				error_p(shell, "fork", FATAL, 1);
			signal_toggle(IGNORE);
			if (pid == 0)
				child_heredoc(shell, cmd, file, i);
			waitpid(pid, &shell->exit_status, 0);
			signal_toggle(INTERACTIVE);
			if (heredoc_2_array(shell, &cmd->redir[i], &file))
				return ;
			shell->heredoc_index++;
		}
		i++;
	}
}

static char	*filename_heredoc(t_minishell *shell)
{
	char	*file;
	char	*tmp;

	tmp = ft_itoa(shell->heredoc_index);
	if (!tmp)
		error(shell, ERR_MALLOC, FATAL, 1);
	file = ft_strjoin("/tmp/heredoc", tmp);
	free(tmp);
	if (!file)
		error(shell, ERR_MALLOC, FATAL, 1);
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

void	write_to_heredoc(t_minishell *shell, char *limit, int fd)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strcmp(str, limit))
		{
			free(str);
			break ;
		}
		if (ft_strchr(str, '$'))
			expand(shell, &str);
		ft_putendl_fd(str, fd);
		free(str);
	}
}
