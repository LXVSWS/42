/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:28:35 by lwyss             #+#    #+#             */
/*   Updated: 2021/12/07 15:57:26 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_data *lx)
{
	if (keycode == 123)
		lx->x1 -= 50 / lx->zoom;
	if (keycode == 126)
		lx->y1 -= 50 / lx->zoom;
	if (keycode == 124)
		lx->x1 += 50 / lx->zoom;
	if (keycode == 125)
		lx->y1 += 50 / lx->zoom;
	if (keycode == 53)
	{
		mlx_destroy_image(lx->mlx, lx->img);
		mlx_destroy_window(lx->mlx, lx->win);
		exit(0);
	}
	fractal(lx);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *lx)
{
	if (button == 4)
	{
		lx->iterations += 7;
		lx->zoom *= 1.25;
		lx->x1 = (x / lx->zoom + lx->x1) - (x / (lx->zoom * 1.25));
		lx->y1 = (y / lx->zoom + lx->y1) - (y / (lx->zoom * 1.25));
	}
	if (button == 5 && lx->iterations > 10)
	{
		lx->iterations -= 7;
		lx->zoom *= 0.75;
		lx->x1 = (x / lx->zoom + lx->x1) - (x / (lx->zoom * 0.75));
		lx->y1 = (y / lx->zoom + lx->y1) - (y / (lx->zoom * 0.75));
	}
	if (button == 1)
		lx->color++;
	fractal(lx);
	return (0);
}

int	mouse_motion_hook(int x, int y, t_data *lx)
{
	lx->mouse_x = x;
	lx->mouse_y = y;
	fractal(lx);
	return (0);
}

void	burningship(t_data *lx, int x, int y)
{
	lx->c_r = x / lx->zoom + lx->x1;
	lx->c_i = y / lx->zoom + lx->y1;
	lx->z_r = 0;
	lx->z_i = 0;
	algo2(lx);
}

void	algo2(t_data *lx)
{
	long double	tmp;

	lx->i = 0;
	while ((lx->z_r * lx->z_r) + (lx->z_i * lx->z_i) < 4 \
	&& lx->i < lx->iterations)
	{
		tmp = lx->z_r * lx->z_r - lx->z_i * lx->z_i + lx->c_r;
		lx->z_r = fabsl(2 * (lx->z_r * lx->z_i)) + lx->c_i;
		lx->z_i = tmp;
		lx->i++;
	}
}
