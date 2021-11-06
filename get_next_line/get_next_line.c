/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:25:22 by lwyss             #+#    #+#             */
/*   Updated: 2021/11/04 18:34:25 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
    static char *s = "";
	char *buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buf)
        return (NULL);
    buf[BUFFER_SIZE] = 0;
    while (read(fd, buf, BUFFER_SIZE))
	    s = ft_strjoin(s, buf);
    free(buf);
	return (s);
}