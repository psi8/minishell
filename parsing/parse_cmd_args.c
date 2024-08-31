#include "../minishell.h"

void	extract_cmd(t_minishell *shell, t_cmd_data *cmd);
void	extract_args(t_minishell *shell, t_cmd_data *cmd);

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
			end = skip_quotes(cmd->line, end);
		end++;
	}
	cmd->cmd = ft_substr(cmd->line, start, end - start);
	if (!cmd->cmd)
		error(shell, MALLOC, FATAL, 1);
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
		error(shell, MALLOC, FATAL, 1);
	cmd->args[0] = ft_strdup(cmd->cmd);
	if (!cmd->args[0])
		error(shell, MALLOC, FATAL, 1);
	if (cmd->arg_count > 1)
		fetch_args(shell, cmd);
	cmd->args[cmd->arg_count] = NULL;
}
