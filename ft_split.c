#include "libft/libft.h"

static int	isep(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

// word = compte les mots
// wordalloc = alloue nb mots et taille mots

char	**ft_split(char const *s, char c)
{
	char	**pp;
	char	*str;
	int		i;

	i = 0;
	pp = malloc(sizeof(char *) * 1 + 1);
	while (!isep((char *)s, c))
		i++;
	printf("%i\n", i);
	str = malloc(sizeof(char) * i + 1);
	str[i] = 0;
	while (i)
		str[i] = s[i];
	*pp = str;
	*(pp + 1) = NULL;
	return (pp);
}

int	main()
{
	char s[] = "Hello";
	char c = 'l';
	char **pp = ft_split(s, c);
	printf("%s\n", *pp);
}
