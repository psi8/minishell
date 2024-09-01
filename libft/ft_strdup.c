/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:58:02 by dlevinsc          #+#    #+#             */
/*   Updated: 2023/10/29 14:53:37 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	long	l;

	l = ft_strlen(src) + 1;
	dst = malloc(l);
	if (!dst)
		return ((char *) 0);
	ft_strlcpy(dst, src, l);
	return (dst);
}
