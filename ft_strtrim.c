#include "libft/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	(void)s1;
	return (char *)(set);
}

int	main()
{
	char s1[] = "hahatesthaha";
	char set[] = "haha";
	printf("%s\n", ft_strtrim(s1, set));
}
