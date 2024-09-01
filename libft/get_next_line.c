/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:41:46 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/04/05 19:53:54 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnl_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

static char	*clean_store(char *store)
{
	char	*new_store;
	char	*ptr;
	size_t	len;

	ptr = ft_gnl_strchr(store, '\n');
	if (!ptr)
	{
		new_store = NULL;
		return (ft_gnl_free(&store));
	}
	else
		len = (ptr - store) + 1;
	if (!store[len])
		return (ft_gnl_free(&store));
	new_store = ft_gnl_substr(store, len, ft_strlen(store) - len);
	ft_gnl_free(&store);
	if (!new_store)
		return (NULL);
	return (new_store);
}

static char	*new_line(char *store)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_gnl_strchr(store, '\n');
	len = (ptr - store) + 1;
	line = ft_gnl_substr(store, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*readbuf(int fd, char *store)
{
	int		resfd;
	char	*buffer;

	resfd = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_gnl_free(&store));
	buffer[0] = '\0';
	while (resfd > 0 && !ft_gnl_strchr(buffer, '\n'))
	{
		resfd = read (fd, buffer, BUFFER_SIZE);
		if (resfd > 0)
		{
			buffer[resfd] = '\0';
			store = ft_gnl_strjoin(store, buffer);
		}
	}
	free(buffer);
	if (resfd == -1)
		return (ft_gnl_free(&store));
	return (store);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	if (!store)
		store = NULL;
	if (fd < 0)
		return (NULL);
	if ((store && !ft_gnl_strchr(store, '\n')) || !store)
		store = readbuf (fd, store);
	if (!store)
		return (NULL);
	line = new_line(store);
	if (!line)
		return (ft_gnl_free(&store));
	store = clean_store(store);
	return (line);
}
