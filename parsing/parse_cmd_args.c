#include "../minishell.h"

void	extract_cmd(t_minishell *shell, t_cmd_data *cmd);
void	extract_args(t_minishell *shell, t_cmd_data *cmd);
static int	count_args(char *line);
void	fetch_args(t_minishell *shell, t_cmd_data *cmd);
char	*fetch_substr(t_minishell *shell, char *line, int start, int len);

void	extract_cmd(t_minishell *shell, t_cmd_data *cmd)
{
	int		start;
	int		end;

	if (shell->status == ERROR)
		return ;
	start = 0;
	while (cmd->line[start] && cmd->line[start] == ' ')
		start++;
	end = start;
	while (cmd->line[end] && cmd->line[end] != ' ')
	{
		if (cmd->line[end] == '\'' || cmd->line[end] == '\"')
			end = quotes_skip(cmd->line, end);
		end++;
	}
	cmd->cmd = ft_substr(cmd->line, start, end - start);
	if (!cmd->cmd)
		error(shell, ERR_MALLOC, FATAL, 1);
	quotes_remove(cmd->cmd);
	change_2_space(cmd->line, start, end);
}

void	extract_args(t_minishell *shell, t_cmd_data *cmd)
{
	if (shell->status == ERROR)
		return ;
	cmd->arg_count = count_args(cmd->line) + 1;
	cmd->args = malloc(sizeof(char *) * (cmd->arg_count + 1));
	if (!cmd->args)
		error(shell, ERR_MALLOC, FATAL, 1);
	cmd->args[0] = ft_strdup(cmd->cmd);
	if (!cmd->args[0])
		error(shell, ERR_MALLOC, FATAL, 1);
	if (cmd->arg_count > 1)
		fetch_args(shell, cmd);
	cmd->args[cmd->arg_count] = NULL;
}

void	fetch_args(t_minishell *shell, t_cmd_data *cmd)
{
	int		i;
	int		start;
	int		k;

	i = 0;
	k = 1;
	while (cmd->line[i])
	{
		while (cmd->line[i] && cmd->line[i] == ' ')
			i++;
		start = i;
		while (cmd->line[i] && cmd->line[i] != ' ')
		{
			if (cmd->line[i] == '\'' || cmd->line[i] == '\"')
				i = quotes_skip(cmd->line, i);
			i++;
		}
		cmd->args[k] = fetch_substr(shell, cmd->line, start, i - start);
		if (!cmd->args[k])
			break ;
		quotes_remove(cmd->args[k]);
		k++;
	}
}

static int	count_args(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			count++;
			while (line[i] && line[i] != ' ')
			{
				if (line[i] == '\'' || line[i] == '\"')
					i = quotes_skip(line, i);
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

char	*fetch_substr(t_minishell *shell, char *line, int start, int len)
{
	char	*substr;

	if (len == 0)
		return (NULL);
	substr = ft_substr(line, start, len);
	if (!substr)
		error(shell, ERR_MALLOC, FATAL, 1);
	return (substr);
}