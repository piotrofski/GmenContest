#include "../includes/header.h"

int	char_is_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *src, char *charset, int start)
{
	char	*new_str;
	int		i;

	i = 0;
	while (char_is_sep(src[start + i], charset) == 0 && src[i])
		i++;
	new_str = (char *)malloc(sizeof (char) * (i + 1));
	if (!new_str)
		return (0);
	i = 0;
	while (char_is_sep(src[start], charset) == 0 && src[i])
	{
		new_str[i] = src[start];
		i++;
		start++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	c_words(char *str, char *charset)
{
	int	i;
	int	num_words;

	i = 0;
	num_words = 0;
	while (str[i])
	{
		while (str[i] && char_is_sep(str[i], charset))
			i++;
		if (str[i] != '\0')
			num_words++;
		while (str[i] && !char_is_sep(str[i], charset))
			i++;
	}
	return (num_words);
}

char	**ft_splitter(char *str, char *charset, char **result)
{
	int	i;
	int	k;
	int	start;

	i = 0;
	start = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && char_is_sep(str[i], charset))
			i++;
		if (str[i] != '\0')
		{
			start = i;
			result[k] = ft_strdup(str, charset, start);
			k++;
		}
		while (str[i] && !(char_is_sep(str[i], charset)))
			i++;
	}
	result[k] = 0;
	return (result);
}

char	**ft_split(char *str, char *charset)
{
	char	**result;

	result = (char **) malloc (sizeof(char *) * (c_words(str, charset) + 1));
	if (!result)
		return (NULL);
	return (ft_splitter(str, charset, result));
}