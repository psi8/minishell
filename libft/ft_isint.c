/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:36:34 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/08/19 22:31:11 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static int	is_moreintmax(int res, char c, int sign)
{
	return (res > __INT_MAX__ / 10
		|| (res == __INT_MAX__ / 10
			&& __INT_MAX__ % 10 + 1 * (sign < 0) < (c - '0')));
}

static t_bool	check_int_digits(char *str, int sign)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (is_moreintmax(res, str[i], sign))
				return (false);
			res = res * 10 + (str[i] - '0');
		}
		else
			return (false);
		i++;
	}
	return (true);
}

t_bool	ft_isint(char *str)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		sign *= 1 - 2 * (str[i++] == '-');
		if (!ft_isdigit(str[i]))
			return (false);
	}
	return (check_int_digits(&str[i], sign));
}
