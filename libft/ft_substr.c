/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:42:34 by dlevinsc          #+#    #+#             */
/*   Updated: 2023/11/04 18:56:15 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		str[0] = 0;
		return (str);
	}
	str = malloc(len * (len <= s_len - start)
			+ (s_len - start) * (len > s_len - start) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len && start + i < s_len)
		str[i] = s[start + i];
	str[i] = 0;
	return (str);
}
