
#include "minishell.h"

char	*get_env(t_minishell *shell, char *search);
void	paths(t_minishell *shell, char **envp);

static void	shlvl_warning(int shlvl)
{
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putnbr_fd(shlvl, 2);
	ft_putendl_fd(") too high, resetting to 1", 2);
}

void	paths(t_minishell *shell, char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if(!ft_strncmp(envp[i], "PATH", 4))
		{
			shell->paths = ft_split(envp[i] + 5, ':');
			if(shell->paths == NULL)
				error(shell, ERR_MALLOC, FATAL, 1);
			return;
		}
		i++;
	}
}

char	*get_env(t_minishell *shell, char *search)
{
	int		i;
	int		len;
	char	*str;
	
	i = 0;
	if (!search)
		return (NULL);
	len = ft_strlen(search);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], search, len))
		{
			if (shell->env[i][len] == '=')
			{
				str = ft_strdup(shell->env[i] + len + 1);
				if (str == NULL)
					error(shell, ERR_MALLOC, FATAL, 1);
				return (str);
			}
		}
		i++;
	}
	return (NULL);
}

static void	export_shlvl(t_minishell *shell, char **shlvl_str)
{
	char	*output;

	rm_fr_array(shell->env, "SHLVL");
	output = ft_strjoin("SHLVL=", *shlvl_str);
	if (!output)
	{
		free(*shlvl_str);
		*shlvl_str = NULL;
		error(shell, ERR_MALLOC, FATAL, 1);
	}
	shell->env = add_to_array(shell, shell->env, output, FREEABLE);
	free(*shlvl_str);
	free(output);
}

void	shlvl_increment(t_minishell *shell)
{
	int		shlvl;
	char	*shlvl_str;

	shlvl_str = get_env(shell, "SHLVL");
	if (!shlvl_str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(shlvl_str);
		if (shlvl < 0)
			shlvl = 0;
		else
			shlvl = shlvl + 1;
		if (shlvl > 1000)
		{
			shlvl_warning(shlvl);
			shlvl = 1;
		}
		free(shlvl_str);
	}
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		error(shell, ERR_MALLOC, FATAL, 1);
	export_shlvl(shell, &shlvl_str);
}