/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 23:50:11 by lwyss             #+#    #+#             */
/*   Updated: 2022/07/25 10:17:29 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	no_detected(t_data *data, char *file)
{
	if (!data->no)
		data->no = strdupmod(file);
	else
		error("Multiple north paths detected");
}

void	so_detected(t_data *data, char *file)
{
	if (!data->so)
		data->so = strdupmod(file);
	else
		error("Multiple south paths detected");
}

void	we_detected(t_data *data, char *file)
{
	if (!data->we)
		data->we = strdupmod(file);
	else
		error("Multiple west paths detected");
}

void	ea_detected(t_data *data, char *file)
{
	if (!data->ea)
		data->ea = strdupmod(file);
	else
		error("Multiple east paths detected");
}

void	f_detected(t_data *data, char *file)
{
	if (!data->f)
		data->f = ft_split(strdupmod(file), ',');
	else
		error("Multiple floor rgb detected");
}

void	c_detected(t_data *data, char *file)
{
	if (!data->c)
		data->c = ft_split(strdupmod(file), ',');
	else
		error("Multiple sky rgb detected");
}
