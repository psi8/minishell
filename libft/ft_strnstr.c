/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:58:24 by dlevinsc          #+#    #+#             */
/*   Updated: 2023/10/29 17:54:56 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!needle[0])
		return ((char *)haystack);
	i = -1;
	while (++i < len && haystack[i])
	{
		j = -1;
		while (needle[++j] && i + j < len)
		{
			if (needle[j] != haystack[i + j])
				break ;
		}
		if (!needle[j])
			return ((char *)(haystack + i));
	}
	return (NULL);
}
