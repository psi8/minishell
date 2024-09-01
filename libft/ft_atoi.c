/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:36:34 by dlevinsc          #+#    #+#             */
/*   Updated: 2023/11/13 19:04:04 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		i;
	long	res;

	res = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign *= 1 - 2 * (str[i++] == '-');
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > __LONG_MAX__ / 10
			|| (res == __LONG_MAX__ / 10 && __LONG_MAX__ % 10 < (str[i] - '0')))
			return (-1 * (sign > 0));
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (sign * (int) res);
}
