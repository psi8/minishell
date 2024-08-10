/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:17:09 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/04/05 20:07:02 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		len = ft_print_str("(null)");
	else
	{
		while (str[len])
			if (ft_ssize_putchar_fd(str[len++], 1) < 0)
				return (-1);
	}
	return (len);
}
