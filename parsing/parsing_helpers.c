
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
