/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:10:26 by lwyss             #+#    #+#             */
/*   Updated: 2021/12/12 17:46:07 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

size_t	strlen(char const *s);
int		intlen(int a);
char	*itoa(int n);
int		atoi(const char *s);
void	atob_calc(char *b, char c, int j);

#endif
