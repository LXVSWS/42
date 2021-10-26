#include "libft/libft.h"

static int	isep(char c1, char c2)
{
	if (c1 == c2)
		return (1);
	return (0);
}

// word = compte les mots
// wordalloc = alloue nb mots et taille mots

char	**ft_split(char const *s, char c)
{
	char	**pp;
	char	*str;
	int		i;
	int		sep;
	int		len;

	i = 0;
	sep = 0;
	len = ft_strlen(s);
	while (s[i])
	{
		if (isep(s[i], c))
			sep++;
		i++;
	}
	pp = malloc(sizeof(char) * (len - sep) + 1);
	*(pp + 1) = NULL;
	str = malloc(sizeof(char) * (len - sep) + 1);
	str[len - sep] = 0;
	i = 0;
	while (!isep(s[i], c))
	{
		str[i] = s[i];
		i++;		
	}
	*pp = str;
	return (pp);
}

int	main()
{
	char s[] = "Hellolhfbefehybflejhyfbsfl";
	char c = 'l';
	char **pp = ft_split(s, c);
	printf("%s\n", *pp);
}
