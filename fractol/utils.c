/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:41:55 by lwyss             #+#    #+#             */
/*   Updated: 2021/12/05 16:32:16 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	initialisation(t_data *lx)
{
	lx->mlx = mlx_init();
	lx->win = mlx_new_window(lx->mlx, W, H, "fractol");
	lx->img = mlx_new_image(lx->mlx, W, H);
	lx->addr = mlx_get_data_addr(lx->img, &lx->bpp, &lx->ll, &lx->endian);
}

void	alchemy(t_data *lx)
{
	if (!lx->toggle)
	{
		lx->iterations = 150;
		lx->zoom = 300;
		lx->x1 = -1.5;
		lx->x2 = 1.5;
		lx->y1 = -1.5;
		lx->y2 = 1.5;
	}
	else if (lx->toggle == 1)
	{
		lx->iterations = 50;
		lx->zoom = 300;
		lx->x1 = -2.1;
		lx->x2 = 0.6;
		lx->y1 = -1.6;
		lx->y2 = 1.2;
	}
}

long double	precision(int n)
{
	long double	tmp;

	tmp = n * 2;
	return (tmp);
}

unsigned int	rgb2int(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}

void	draw(t_data *lx, int i, int x, int y)
{
	t_rgb	rgb;
	char	*dst;

	if (i == lx->iterations)
	{
		dst = lx->addr + (y * lx->ll + x * (lx->bpp / 8));
		*(unsigned int *)dst = 0x000000;
	}
	else
	{
		rgb.r = sin(0.4 * i + (lx->color + 2)) * 127 + 128;
		rgb.g = sin(0.2 * i + (lx->color + 2)) * 127 + 128;
		rgb.b = sin(0.2 * i + (lx->color + 3)) * 127 + 128;
		dst = lx->addr + (y * lx->ll + x * (lx->bpp / 8));
		*(unsigned int *)dst = rgb2int(rgb);
	}
}
