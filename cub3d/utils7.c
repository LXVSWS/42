/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 00:04:04 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/24 00:18:08 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c_detected(t_data *data, char *file)
{
	if (!data->c)
		data->c = ft_split(strdupmod(file), ',');
	else
		error("Multiple sky paths detected");
}
