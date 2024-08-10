/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_number.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:28:27 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/04/05 20:06:17 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_unsigned_number(unsigned int num)
{
	int	i;

	i = 0;
	if (num / 10)
	{
		i = 1 + ft_print_unsigned_number(num / 10);
		if (i == 0)
			return (-1);
		if (ft_ssize_putchar_fd(num % 10 + '0', 1) < 0)
			return (-1);
	}
	else
	{
		if (ft_ssize_putchar_fd(num % 10 + '0', 1) < 0)
			return (-1);
		return (1);
	}
	return (i);
}
