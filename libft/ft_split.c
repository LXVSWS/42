#include "libft.h"

static int	countword(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
		}
		if ((s[i + 1] == 0 || s[i + 1] == c) && s[i] != c && s[i])
			word++;
		i++;
	}
	return (word);
}

static int	sizeword(char *s, char sep)
{
	static int	i = 0;
	int	size = 0;

	while (s[i] && s[i] != sep)
	{
		size++;
		i++;
	}
	if (s[i] == sep)
	{
		while (s[i] == sep)
			i++;
	}
	return (size);
}

static	char *wordalloc(int size)
{
	char *word;

	word = malloc(sizeof(char) * size + 1);
	if (!word)
		return (NULL);
	word[size] = 0;
	return (word);
}

static int	offset(char *s, char sep)
{
	static int	i = 0;

	while (s[i] && s[i] != sep)
		i++;
	if (s[i] == sep)
	{
		while (s[i] == sep)
			i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**pp;
	int		word;
	int		wsize;
	int		os;
	int		i;
	int		j;

	os = 0;
	i = 0;
	j = 0;
	word = countword((char *)s, c);
	printf("%i\n", word);
	pp = malloc(sizeof(char *) * word + 1);
	while (i < word)
	{
		wsize = sizeword((char *)s, c);
		*(pp + i) = wordalloc(wsize);
		if (!pp[i])
			return (NULL);
		while (j < wsize)
		{
			pp[i][j] = s[os];
			j++;
			os++;
		}
		pp[i][j] = 0;
		j = 0;
		os = offset((char *)s, c);
		i++;
	}
	*(pp + i) = NULL;
	return (pp);
}
/*
int	main()
{
	char s[] = "HellxbonjouxxcavaxHahaoxHello";
	char c = 'x';
	char **pp = ft_split(s, c);
	int	i = 0;
	while (pp[i])
	{
		printf("%s\n", pp[i]);
		i++;
	}
}
*/
