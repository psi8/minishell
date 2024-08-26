#include "minishell.h"

void	expand(t_minishell *shell, char **str);
static void	exp_env(t_minishell *shell, char **str, int *i);
static char	*get_exp(t_minishell *shell, char *str);
static char *get_exit_status(t_minishell *shell);

void	expand(t_minishell *shell, char **str)
{
	int		i;
	int		in_doubles;

	if (shell->status == ERROR)
		return ;
	i = 0;
	in_doubles = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\"')
			in_doubles = !in_doubles;
		if ((*str)[i + 1] && (*str)[i] == '\'' && !in_doubles)
			i = skip_quotes(*str, i);
		if ((*str)[i + 1] && (*str)[i] == '$' && (*str)[i + 1] != ' ')
		{
			exp_env(shell, str, &i);
			continue ;
		}
		i++;
	}
}

static void	exp_env(t_minishell *shell, char **str, int *i)
{
	char	*new;
	char	*value;
	int		start;

	(*i)++;
	start = *i;
	if (fin_char((*str)[start]) && (*str)[start + 1] == '\0')
		return ;
	value = get_exp(shell, &(*str)[start]);
	(*i) = start + ft_strlen(value) - 1;
	new = join_and_free(ft_substr(*str, 0, start - 1), value);
	if (!new)
		error(shell, MALLOC_ERR, FATAL, 1);
	if ((*str)[start] != '?')
		while (!fin_char((*str)[start]))
			start++;
	else
		start++;
	if ((*str)[start])
		new = join_and_free(new, ft_strdup(&(*str)[start]));
	if (!new)
		error(shell, MALLOC_ERR, FATAL, 1);
	free(*str);
	*str = new;
}

static int	fin_char(char c)
{
	if (c == '/' 
		|| c == '\"' 
		|| c == '\''  
		|| c == '\0' 
		|| c == ' ' 
		|| c == '$'
		|| c == '=' 
		|| c == ':'
		|| c == '@')
		return (1);
	return (0);
}

static char	*get_exp(t_minishell *shell, char *str)
{
	int		len;
	char	*env;
	char	*value;

	len = 0;
	if (str[len] == '?')
		return (get_exit_status(shell));
	while (!fin_char(str[len]))
		len++;
	if (len == 0)
		return (empty_strdup(shell));
	env = ft_substr(str, 0, len);
	if (!env)
		error(shell, MALLOC_ERR, FATAL, 1);
	value = ft_getenv(shell, env);
	if (!value)
		value = empty_strdup(shell);
	free(env);
	return (value);
}

static char *get_exit_status(t_minishell *shell)
{
	char	*value;

	if (shell->exit_status > 255)
		value = ft_itoa(WEXITSTATUS(shell->exit_status));
	else
		value = ft_itoa(shell->exit_status);
	if (!value)
		error(shell, MALLOC_ERR, FATAL, 1);
	return (value);
}