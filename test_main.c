/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:04:58 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/03 15:04:58 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Прототипы тестовых функций
void test_is_builtin_without_output(void);
void test_is_builtin(void);
void test_call_builtin(t_minishell *shell);

t_hmap	**init_hmap(char **env)
{
	char	*hash_key;
	t_hmap	**hashmap;
	int		j;
	int		i;

	hashmap = (t_hmap **)malloc(sizeof(t_hmap *));
	if (!hashmap)
		exit(EXIT_FAILURE);
	*hashmap = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != 0 && env[i][j] != '=')
			j++;
		hash_key = malloc(j + 1);
		if (!hash_key)
			exit(1);
		ft_strncpy(hash_key, env[i], j);
		hash_key[j] = '\0';
		add_new_var(hashmap, hash_key, ft_strchr(env[i], '=') + 1);
		free(hash_key);
		i++;
	}
	return (hashmap);
}

void	add_new_var(t_hmap **v, char *akey, char *avalue)
{
	t_hmap	*node;
	t_hmap	*temp;

	if (akey[0] == ' ')
		node = hmap_new(akey + 1, NULL);
	else
		node = hmap_new(akey, avalue);
	if (!node)
		return ;
	if (*v == NULL)
		*v = node;
	else
	{
		temp = *v;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}
// Инициализация структуры данных t_minishell
void init_minishell(t_minishell **shell, char **envp, t_cmd_data *cmd_data)
{
    *shell = (t_minishell *)malloc(sizeof(t_minishell));
    if (!(*shell))
        exit(MALLOC_ERR);

    (*shell)->hashmap = init_hmap(envp);
    (*shell)->pwd = getcwd(NULL, 0);
    (*shell)->oldpwd = NULL;
    (*shell)->exit_status = 0;
    (*shell)->root = NULL;
    (*shell)->is_parent = true;
    (*shell)->is_oldpwd_unset = true;
    (*shell)->cmd_data.cmd = NULL;
    (*shell)->cmd_data.argv = NULL;
    (*shell)->cmd_data.cmd_paths = NULL;
    (*shell)->cmd_data.cmd_path = NULL;
    (*shell)->cmd_data.cmd_line = NULL;
    (*shell)->cmd_data.hashmap = (*shell)->hashmap;
}

// Завершение работы shell и освобождение ресурсов
void terminate_minishell(t_minishell **shell, int status)
{
    if (*shell)
    {
        free_minishell(*shell);
        *shell = NULL;
    }
    exit(status);
}

// Тестовая функция для is_builtin_without_output
void test_is_builtin_without_output(void)
{
    t_command cmd;

    char *cmds[] = { "cd", "exit", "unset", "export", "echo", "pwd", "env", NULL };

    for (int i = 0; cmds[i]; i++)
    {
        cmd.cmd = cmds[i];
        printf("Testing is_builtin_without_output with command '%s': %s\n", cmds[i], is_builtin_without_output(&cmd) ? "true" : "false");
    }
}

// Тестовая функция для is_builtin
void test_is_builtin(void)
{
    char *cmds[] = { "cd", "exit", "unset", "export", "echo", "pwd", "env", "nonexistent", NULL };

    for (int i = 0; cmds[i]; i++)
    {
        printf("Testing is_builtin with command '%s': %s\n", cmds[i], is_builtin(cmds[i]) ? "true" : "false");
    }
}

// Тестовая функция для call_builtin
void test_call_builtin(t_minishell *shell)
{
    t_command cmd;
    char *cmds[][3] = {
        { "echo", "Hello, World!", NULL },
        { "pwd", NULL },
        { "env", NULL },
        { "cd", "/", NULL },
        { "export", "TEST_VAR=test", NULL },
        { "unset", "TEST_VAR", NULL },
        { "exit", NULL },
        { NULL }
    };

    for (int i = 0; cmds[i][0]; i++)
    {
        cmd.cmd = cmds[i][0];
        cmd.argv = cmds[i];
        printf("Testing call_builtin with command '%s': \n", cmds[i][0]);
        call_builtin(shell, &cmd);
    }
}

// Основная функция
int main(int argc, char **argv, char **envp)
{
    t_minishell *shell;

    // Инициализация структуры данных shell
    init_minishell(&shell, envp, NULL);

    // Тестирование функций
    test_is_builtin_without_output();
    test_is_builtin();
    test_call_builtin(shell);

    // Завершение работы shell
    terminate_minishell(&shell, shell->exit_status);
    return 0;
}
