/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:47:19 by psitkin           #+#    #+#             */
/*   Updated: 2024/08/31 20:01:55 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define SYNTAX_QUOTES "syntax error with unclosed quotes"

# define ERR_MALLOC "Error: malloc unexpectedly failed"
# define ERR_PIPE "unexpected error while opening pipe"
# define ERR_EXEC "unexpected error while executing command"
# define ERR_CWD "unexpected error while executing getcwd"
# define ERR_FORK "unexpected error while creating fork"
# define ERR_EXP "not a valid identifier"
# define ERR_HD "unexpected error while creating heredoc temp file"

# define ERR_QUOTES "syntax error unexpected EOF while look for matching ` "
# define SYNTAX_PIPE "syntax error near unexpected token `|'"
# define SYNTAX_INFILE "syntax error near unexpected token `<'"
# define SYNTAX_OUTFILE "syntax error near unexpected token `>'"
# define SYNTAX_NL "syntax error near unexpected token `newline'"
# define SYNTAX_QUOTES "syntax error with unclosed quotes"

# define ERR_CMD ": command not found"
# define ERR_NOFILE ": no such file or directory"
# define ERR_OLDPWD "cd: OLDPWD not set"
# define ERR_HOME "cd: HOME not set"
# define ERR_PERM ": permission denied"
# define ERR_DIR ": is a directory"

#endif