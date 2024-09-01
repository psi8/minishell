/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:57:57 by dlevinsc          #+#    #+#             */
/*   Updated: 2023/10/28 20:17:44 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (dest > src)
		while (n--)
			*(char *)(dest + n) = *(char *)(src + n);
	else if (dest < src)
		while (++i < n)
			*(char *)(dest + i) = *(char *)(src + i);
	return (dest);
}
