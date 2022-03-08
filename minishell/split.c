#include "minishell.h"

static int	countword(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			word++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (word);
}

static int	sizeword(char *s, char sep)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != sep)
		i++;
	return (i);
}

static char	*wordalloc(int size)
{
	char	*word;

	word = malloc(sizeof(char) * size + 1);
	if (!word)
		return (NULL);
	word[size] = 0;
	return (word);
}

static char	**wordcopy(char **pp, char *s, char c)
{
	int		os;
	int		i;
	int		j;
	int		wsize;

	os = 0;
	i = -1;
	while (++i < countword((char *)s, c))
	{
		while (s[os] == c)
			os++;
		wsize = sizeword((char *)&s[os], c);
		pp[i] = wordalloc(wsize);
		j = 0;
		while (j < wsize)
			pp[i][j++] = s[os++];
		pp[i][j] = 0;
	}
	*(pp + i) = NULL;
	return (pp);
}

char	**split(char const *s, char c)
{
	char	**pp;

	if (!s)
		return (NULL);
	pp = malloc(sizeof(char *) * (countword((char *)s, c) + 1));
	if (!pp)
		return (NULL);
	pp = wordcopy(pp, (char *)s, c);
	return (pp);
}
