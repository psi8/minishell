
#include <minishell.h>

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s == NULL)
		return(NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = (char *) malloc(sizeof(char) * (len + 1))
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + 1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*join_and_free(char *str1, char *str2)
{
	char	*new;

	if (!str1)
	{
		str1 = ft_calloc(1, 1);
		if (!str1)
			return (NULL);
	}
	new = ft_strjoin(str1, str2);
	if (!new)
	{
		free(str1);
		free(str2);
		return (NULL);
	}
	free(str1);
	free(str2);
	return (new);
}

char	*empty_strdup(t_minishell *shell)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		error(shell, MALLOC_ERR, FATAL, 1);
	return (str);
}