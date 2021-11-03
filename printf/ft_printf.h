/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 23:15:32 by lwyss             #+#    #+#             */
/*   Updated: 2021/11/04 00:01:54 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *s, ...);
int	ft_getflag(char c, va_list ap);
int	ft_putsize(unsigned long long i, char *base, void *ptr);
int	print_c(char c);
int	print_s(char *s);
int	print_id(int i);

#endif
