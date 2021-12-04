#ifndef FRACTOL_H
# define FRACTOL_H
# define W 1000
# define H 1000

#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct  s_data
{
    void		*mlx;
    void		*win;
	void		*img;
	char		*addr;
	char		type;
    int			iterations;
    long double	zoom;
    long double	x1;
    long double x2;
    long double y1;
    long double y2;
	int			bpp;
	int			ll;
	int			endian;
    int			mouse_x;
    int			mouse_y;
    int         toggle;
}               t_data;

typedef struct	s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}				t_rgb;

#endif
