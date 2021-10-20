#include "libft/libft.h"

int		isep(char char_of_s1, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (char_of_s1 == charset[i++])
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int i;
	char *s = NULL;

	i = 0;
	while (isep(s1[i], (char *)set))
		i++;
	printf("%i\n", i);
	return (s);
}

int	main()
{
	char s1[] = "hahatesthaha";
	char set[] = "ha";
	printf("%s\n", ft_strtrim(s1, set));
}
