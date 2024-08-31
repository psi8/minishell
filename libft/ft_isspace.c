/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libft/ft_isspace.c
/*   Created: 2024/08/25 11:35:18 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/25 11:35:25 by dlevinsc         ###   ########.fr       */
=======
/*   Created: 2024/08/11 21:35:23 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/21 21:58:42 by psitkin          ###   ########.fr       */
>>>>>>> origin/pavel:exit.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<< HEAD:libft/ft_isspace.c
int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
=======
#include <minishell.h>

void	exit_shell(t_minishell *shell)
{
	if (isatty(STDIN_FILENO))
	{
		ft_putstr_fd("EXIT", 2);
		ft_putchar_fd('\n', 2);
	}
	array_free(&shell->env);
	all_free(shell);
	signal_toggle(DEFAULT);
	exit(shell->exit_status);
}

void	free_and_exit(t_minishell *shell, int status)
{
	if (shell->parent_redir)
		restore_std(shell);
	all_free(shell);
	array_free(&shell->env);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->old_pwd)
		free(shell->old_pwd);
	signal_toggle(DEFAULT);
	exit(status);
>>>>>>> origin/pavel:exit.c
}
