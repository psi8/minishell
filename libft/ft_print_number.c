/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:39:04 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/04/05 20:08:02 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_number(int num)
{
	int	len;
	int	tmp;

	len = 0;
	if (num < 0)
	{
		if (ft_ssize_putchar_fd('-', 1) < 0)
			return (-1);
		num *= -1;
		len = 1;
	}
	tmp = ft_print_unsigned_number((unsigned int) num);
	if (tmp < 0)
		return (-1);
	len += tmp;
	return (len);
}
