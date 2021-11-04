/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:05:56 by lwyss             #+#    #+#             */
/*   Updated: 2021/11/04 17:06:00 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*str;
	int		i;

	size = ft_strlen(s);
	str = (char *) malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static int	intlen(int a)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	if (a <= 0)
	{
		neg = 1;
		a *= -1;
	}
	while (a > 0)
	{
		a /= 10;
		i++;
	}
	return (i + neg);
}

char	*ft_itoa(int n)
{
	int		len;
	int		neg;
	char	*s;

	if (n <= -2147483648)
		return (ft_strdup("-2147483648"));
	neg = 0;
	len = intlen(n);
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	s[len] = 0;
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
		neg = 1;
	}
	while (len-- > 0 + neg)
	{
		s[len] = n % 10 + 48;
		n /= 10;
	}
	return (s);
}
