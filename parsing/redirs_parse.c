#include "minishell.h"

//list of func
void	redir_extract(t_minishell *shell, t_cmd_data *cmd);
static int redir_check(t_minishell *shell, t_cmd_data *cmd);


void	redir_extract(t_minishell *shell, t_cmd_data *cmd)
{
	t_parsed_data	pars;

	init_t_parse(&pars);
	if ()
}

static int redir_check(t_minishell *shell, t_cmd_data *cmd)
{
	int	i;

	i = 0;
	while (cmd->line[i])
	{
		if (cmd->line[i] == '\'' || cmd->line[i] == '\"')
			i = quotes_skip(cmd->line, i);
		if (cmd->line[i] == '>' || cmd->line[i] == '<')
		{
			if (cmd->line[i + 1] != '\"' && cmd->line[i + 1] != '\'')
			{
				if (wrong_arrows(shell, cmd->line, cmd->line[i], i + 1))
					return (1);
			}
			if (cmd->line [i + 1] == '>' || cmd->line[i + 1] == '<')
				i++;
			cmd->redir_count++;
		}
		i++;
	}
	if (cmd->redir_count == 0)
		return (1);
	return (0);
}