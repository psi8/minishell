/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:58:14 by dlevinsc          #+#    #+#             */
/*   Updated: 2023/10/29 17:54:54 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = -1;
	while (++a < n && (s1[a] || s2[a]))
	{
		if (s1[a] != s2[a])
			return ((unsigned char) s1[a] - (unsigned char) s2[a]);
	}
	return (0);
}
