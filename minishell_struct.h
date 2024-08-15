/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:23:09 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/15 22:07:06 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef enum	e_exit_status
{
	FATAL,
	SYNTAX,
	ERROR,
	RUNNING,
	EXECUTE,
	EXPORT,
	UNSET,
	FREEABLE,
	GENERIC_ERR,
	CMD_ARG_ERR,
	CMD_PD_FAIL = 126,
	CMD_NF_FAIL = 127,
	MALLOC_ERR = 200,
	SYSTEM_ERR = 201,
	CHDIR_ERR = 202,
	GETCWD_ERR = 203,
	UNEXPECTED_EXIT = 255,
	SYNTAX_ERR = 258,
	EXECVE_FAIL = 300,
	FORK_FAIL = 400,
	PIPE_FAIL = 500,
	DUP_FAIL = 600,
}	t_exit_status;

typedef enum	e_signals
{
	DEFAULT,
	INTERACTIVE,
	HEREDOC,
	IGNORE,
}	t_signals;

typedef struct s_parsed_data
{
	int		i;
	int		j;
	int		k;
	char	quote;
	int		in_quotes;
	int		inside_singles;
	int		inside_doubles;
}	t_parsed_data;

typedef struct s_cmd_data
{
	char	*cmd;
	char	*line;
	char	**redir;
	char	**args;
	int		redir_count;
	int		index;
	int		infile;
	int		out;
	int		arg_count;
}	t_cmd_data;

typedef struct s_minishell
{
	char			**env;
	char			*line;
	t_cmd_data		*cmd_tree;
	char			**paths;
	int				cmd_count;
	t_exit_status	status;
	int				exit_status;
	int				*pid;
	int				pid_allocated;
	int				**pipe;
	int				pipes_allocated;
	int				heredoc_index;
	int				std_in;
	int				std_out;
	int				parent_redir;
	char			*pwd;
	char			*old_pwd;
}	t_minishell;

enum	e_characters
{
	NULL_TERM,
	HT = 9,
	NL = 10,
	L_REDIR_SEPARATOR = 29,
	R_REDIR_SEPARATOR = 30,
	SEPARATOR = 31,
	SPACE = 32,
	D_QUO = 34,
	D_SIGN = 36,
	AND = 38,
	S_QUO = 39,
	O_ROU = 40,
	C_ROU = 41,
	STAR = 42,
	DASH = 45,
	DOT = 46,
	SLASH = 47,
	COLON = 58,
	SEMICOLON = 59,
	REDIR_L = 60,
	EQUAL = 61,
	REDIR_R = 62,
	Q_MARK = 63,
	BSLASH = 92,
	UNDERLINE = 95,
	N_LOW = 110,
	PIPE = 124,
};

#endif