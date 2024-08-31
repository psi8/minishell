#include "minishell.h"

//list of func
void	redir_extract(t_minishell *shell, t_cmd_data *cmd);
static int redir_check(t_minishell *shell, t_cmd_data *cmd);


void	redir_extract(t_minishell *shell, t_cmd_data *cmd)
{
	t_parsed_data	pars;

	init_t_parse(&pars);
	if (redir_check(shell, cmd))
		return ;
	cmd->redir = (char **)malloc(sizeof(char *) * (cmd->redir_count + 1));
	if (!cmd->redir)
		error(shell, MALLOC_ERR, FATAL, 1);
	while (cmd->line[p.i])
	{
		if (cmd->line[pars.i] == '\'' || cmd->line[pars.i] == '\"')
			pars.i = skip_quotes(cmd->line, pars.i) + 1;
		else if (cmd->line[pars.i] == '>' || cmd->line[pars.i] == '<')
		{
			pars.j = pars.i;
			cmd->redir[pars.k] = get_redirection(shell, cmd->line, &pars.i);
			tidy_format(shell, cmd, pars.k);
			replace_with_spaces(cmd->line, pars.j, pars.i);
			pars.k++;
		}
		else
			pars.i++;
	}
	cmd->redir[pars.k] = NULL;
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