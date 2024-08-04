/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:23:09 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/04 17:43:30 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

enum	e_exit_status
{
	SUCCESS,
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
};

enum	e_signals
{
	DEFAULT,
	INTERACTIVE,
	HEREDOC,
	IGNORE,
};

enum	e_signals_echo
{
	IMPLICIT,
	EXPLICIT,
};

typedef struct s_parsed_data
{
	int		type;
	char	*block_left;
	char	*block_right;
}	t_parsed_data;

typedef struct s_token
{
	int				type;
	struct s_token	*left;
	struct s_token	*right;
}	t_token;

typedef struct s_cmd
{
	int		type;
	t_token	*redir;
	char	*cmd;
}	t_cmd;

typedef struct s_redir
{
	int		type;
	char	**redir;
}	t_redir;

typedef struct s_hash_map
{
	char						*key;
	char						*value;
	struct s_hash_map			*next;
}	t_hash_map;

typedef struct s_command_data
{
	char			*cmd;
	char			*cmd_line;
	char			**cmd_paths;
	char			*cmd_path;
	char			**argv;
	t_hash_map		**hmap;
}	t_command_data;

typedef struct s_minishell
{
	int						fd_output;
	char					**command;
	t_hash_map				**hmap;
	int						exit_status;
	char					*pwd;
	char					*oldpwd;
	t_token					*root;
	bool					parent;
	bool					unset_oldpwd;
	t_command_data			cmd_data;
}	t_minishell;

typedef struct s_expansion_state
{
	char			**result;
	char			**str;
	int				*i;
	int				last_status;
	t_minishell		*minish;
	int				*single_quotes;
	int				*double_quotes;
}	t_expansion_state;

enum	e_types
{
	T_PIPE,
	T_COMMAND,
	T_REDIR,
};

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