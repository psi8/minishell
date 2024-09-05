
#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void initialize_minishell_struct(t_minishell *minishell, char **envp) {
    int i;

    // Initialize the environment variables (env) from envp
    i = 0;
    while (envp[i]) {
        i++;
    }
    minishell->env = (char **)malloc((i + 1) * sizeof(char *));
    i = 0;
    while (envp[i]) {
        minishell->env[i] = strdup(envp[i]);
        i++;
    }
    minishell->env[i] = NULL; // NULL-terminated array

    // Initialize paths (simulating $PATH environment variable split by ':')
    minishell->paths = (char **)malloc(3 * sizeof(char *));
    minishell->paths[0] = strdup("/usr/local/bin");
    minishell->paths[1] = strdup("/usr/bin");
    minishell->paths[2] = NULL; // NULL-terminated array

    // Simulate reading the command line
    minishell->line = strdup("cat 1.txt | grep aaa | echo $PATH");

    // Allocate memory for command tree (3 commands)
    minishell->cmd_tree = (t_cmd_data *)malloc(3 * sizeof(t_cmd_data));

    // Initialize individual commands
    // Command 1: "cat 1.txt"
    minishell->cmd_tree[0].cmd = strdup("cat");
    minishell->cmd_tree[0].args = (char **)malloc(3 * sizeof(char *));
    minishell->cmd_tree[0].args[0] = strdup("cat");
    minishell->cmd_tree[0].args[1] = strdup("1.txt");
    minishell->cmd_tree[0].args[2] = NULL; // NULL-terminated array
    minishell->cmd_tree[0].redir = NULL; // No redirection in this command
    minishell->cmd_tree[0].redir_count = 0;
    minishell->cmd_tree[0].infile = -1;
    minishell->cmd_tree[0].out = -1;
    minishell->cmd_tree[0].index = 0;
    minishell->cmd_tree[0].arg_count = 2;

    // Command 2: "grep aaa"
    minishell->cmd_tree[1].cmd = strdup("grep");
    minishell->cmd_tree[1].args = (char **)malloc(3 * sizeof(char *));
    minishell->cmd_tree[1].args[0] = strdup("grep");
    minishell->cmd_tree[1].args[1] = strdup("aaa");
    minishell->cmd_tree[1].args[2] = NULL; // NULL-terminated array
    minishell->cmd_tree[1].redir = NULL; // No redirection in this command
    minishell->cmd_tree[1].redir_count = 0;
    minishell->cmd_tree[1].infile = -1;
    minishell->cmd_tree[1].out = -1;
    minishell->cmd_tree[1].index = 1;
    minishell->cmd_tree[1].arg_count = 2;

    // Command 3: "echo $PATH"
    minishell->cmd_tree[2].cmd = strdup("echo");
    minishell->cmd_tree[2].args = (char **)malloc(3 * sizeof(char *));
    minishell->cmd_tree[2].args[0] = strdup("echo");
    minishell->cmd_tree[2].args[1] = strdup("$PATH");
    minishell->cmd_tree[2].args[2] = NULL; // NULL-terminated array
    minishell->cmd_tree[2].redir = NULL; // No redirection in this command
    minishell->cmd_tree[2].redir_count = 0;
    minishell->cmd_tree[2].infile = -1;
    minishell->cmd_tree[2].out = -1;
    minishell->cmd_tree[2].index = 2;
    minishell->cmd_tree[2].arg_count = 2;

    // Set the number of commands
    minishell->cmd_count = 3;

    // Initialize the status and other fields
    minishell->status = RUNNING;
    minishell->exit_status = 0;
    minishell->pid = NULL;
    minishell->pid_allocated = 0;
    minishell->pipe = NULL;
    minishell->pipes_allocated = 0;
    minishell->heredoc_index = 0;
    minishell->std_in = 0;
    minishell->std_out = 1;
    minishell->parent_redir = 0;
    minishell->pwd = strdup("/home/user");
    minishell->old_pwd = strdup("/home");
}

int test_main(char **envp)
{
    t_minishell minishell;
    int i, j;

    // Initialize the minishell structure
    initialize_minishell_struct(&minishell, envp);

    // Example usage: print the commands and arguments
    i = 0;
    while (i < minishell.cmd_count) {
        printf("Command %d: %s\n", i + 1, minishell.cmd_tree[i].cmd);
        j = 0;
        while (j < minishell.cmd_tree[i].arg_count) {
            printf("  Arg %d: %s\n", j + 1, minishell.cmd_tree[i].args[j]);
            j++;
        }
        i++;
    }

    //RUN

    process_execution(&minishell);

    // Free allocated memory (not fully implemented for brevity)
    free(minishell.line);
    free(minishell.pwd);
    free(minishell.old_pwd);

    i = 0;
    while (minishell.env[i]) {
        free(minishell.env[i]);
        i++;
    }
    free(minishell.env);

    i = 0;
    while (minishell.paths[i]) {
        free(minishell.paths[i]);
        i++;
    }
    free(minishell.paths);

    i = 0;
    while (i < minishell.cmd_count) {
        free(minishell.cmd_tree[i].cmd);
        j = 0;
        while (j < minishell.cmd_tree[i].arg_count) {
            free(minishell.cmd_tree[i].args[j]);
            j++;
        }
        free(minishell.cmd_tree[i].args);
        i++;
    }
    free(minishell.cmd_tree);

    return 0;
}

void print_cmd(t_minishell *minishell)
{
    int i = 0;
    int j;
       
    while (i < minishell->cmd_count) 
    {
        printf("Command %d: %s\n", i + 1, minishell->cmd_tree[i].cmd);
        j = 0;
        while (j < minishell->cmd_tree[i].arg_count) {
            printf("  Arg %d: %s\n", j + 1, minishell->cmd_tree[i].args[j]);
            j++;
        }
        i++;
    }
}

