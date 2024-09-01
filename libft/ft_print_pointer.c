/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:14:27 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/04/05 20:07:22 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	put_ptr(unsigned long long num)
{
	int	i;

	i = 0;
	if (num < 16)
	{
		if (ft_ssize_putchar_fd(LHEX[num], 1) < 0)
			return (-1);
		return (1);
	}
	i = 1 + put_ptr(num / 16);
	if (i == 0)
		return (-1);
	if (put_ptr(num % 16) < 0)
		return (-1);
	return (i);
}

int	ft_print_pointer(unsigned long int ptr)
{
	if (ft_print_str("0x") < 0)
		return (-1);
	return (2 + put_ptr(ptr));
}
