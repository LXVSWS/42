#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	int cp;
	int cpp;

	cp = 0;
	cpp = 0;
	if (ac == 2)
	{
		cp = ft_printf("xxx%sxxx%ixxx%cxxx%dxxx%uxxx%%xxx%xxxx%pxxx", av[1], -198, 'c', -843, 4, 123456789, (void *)4548);
		ft_putchar_fd('\n', 1);
		cpp = printf("xxx%sxxx%ixxx%cxxx%dxxx%uxxx%%xxx%xxxx%pxxx", av[1], -198, 'c', -843, 4, 123456789, (void *)4548);
		printf("\nmy:%i\nor:%i\n", cp, cpp);
	}
}
