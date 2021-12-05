/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:50:57 by lwyss             #+#    #+#             */
/*   Updated: 2021/12/05 15:10:51 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	fractal(t_data *lx)
{
	long double		x;
	long double		y;
	int				i;

	x = -1;
	while (++x < W)
	{
		y = -1;
		while (++y < H)
		{
			if (!lx->toggle)
				julia(lx, x, y);
			else if (lx->toggle == 1)
				mandelbrot(lx, x, y);
			i = 0;
			lx->z_r2 = lx->z_r * lx->z_r;
			lx->z_i2 = lx->z_i * lx->z_i;
			while (lx->z_r2 + lx->z_i2 < 4 && i < lx->iterations)
			{
				lx->z_i = lx->z_r * lx->z_i;
				lx->z_i += lx->z_i;
				lx->z_i += lx->c_i;
				lx->z_r = lx->z_r2 - lx->z_i2 + lx->c_r;
				lx->z_r2 = lx->z_r * lx->z_r;
				lx->z_i2 = lx->z_i * lx->z_i;
				i++;
			}
			draw(lx, i, x, y);
		}
	}
	mlx_put_image_to_window(lx->mlx, lx->win, lx->img, 0, 0);
	if (!lx->toggle)
		mlx_string_put(lx->mlx, lx->win, 10, 10, 0x000000, "Ensemble de Julia");
	else if (lx->toggle == 1)
		mlx_string_put(lx->mlx, lx->win, 10, 10, 0x000000, \
		"Ensemble de Mandelbrot");
	return (0);
}

void	julia(t_data *lx, int x, int y)
{
	lx->c_r = precision(lx->mouse_x) / W - 1.5;
	lx->c_i = precision(lx->mouse_y) / H - 1.5;
	lx->z_r = x / lx->zoom + lx->x1;
	lx->z_i = y / lx->zoom + lx->y1;
}

void	mandelbrot(t_data *lx, int x, int y)
{
	lx->c_r = x / lx->zoom + lx->x1;
	lx->c_i = y / lx->zoom + lx->y1;
	lx->z_r = 0;
	lx->z_i = 0;
}

int	main(int ac, char **av)
{
	t_data	lx;

	if (ac == 2 && (*av[1] == 'j' || *av[1] == 'm'))
	{
		initialisation(&lx);
		if (*av[1] == 'j')
			mlx_hook(lx.win, 6, 0, mouse_motion_hook, &lx);
		if (*av[1] == 'm')
			lx.toggle = 1;
		alchemy(&lx);
		fractal(&lx);
		mlx_key_hook(lx.win, key_hook, &lx);
		mlx_mouse_hook(lx.win, mouse_hook, &lx);
		mlx_loop(lx.mlx);
	}
	else
		printf("------------------------\nParamètres :\nj ->\
		Ensemble de Julia\nm -> Ensemble de Mandelbrot\n");
	return (0);
}
