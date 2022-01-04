/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:10:26 by lwyss             #+#    #+#             */
/*   Updated: 2022/01/04 17:11:16 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

void	sendbits(char c, int pid);
size_t	strlen(char const *s);
int		intlen(int a);
char	*itoa(int n);
int		atoi(const char *s);

#endif
