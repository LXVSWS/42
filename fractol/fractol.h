/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:51:06 by lwyss             #+#    #+#             */
/*   Updated: 2021/12/05 16:02:25 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define W 1000
# define H 1000

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			iterations;
	long double	zoom;
	long double	x1;
	long double	x2;
	long double	y1;
	long double	y2;
	long double	c_r;
	long double	c_i;
	long double	z_r;
	long double	z_i;
	long double	z_r2;
	long double	z_i2;
	int			bpp;
	int			ll;
	int			endian;
	int			mouse_x;
	int			mouse_y;
	char		toggle;
}				t_data;

typedef struct s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}				t_rgb;

void			fractal(t_data *lx);
void			julia(t_data *lx, int x, int y);
void			mandelbrot(t_data *lx, int x, int y);
int				algo(t_data *lx);
int				key_hook(int keycode, t_data *lx);
int				mouse_hook(int button, int x, int y, t_data *lx);
int				mouse_motion_hook(int x, int y, t_data *lx);
void			initialisation(t_data *lx);
void			alchemy(t_data *lx);
long double		precision(int n);
unsigned int	rgb2int(t_rgb rgb);
void			draw(t_data *lx, int i, int x, int y);

#endif
