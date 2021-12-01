#ifndef FRACTOL_H
# define FRACTOL_H
# define W 1000
# define H 1000

#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_data
{
    void    *mlx;
    void    *win;
	void	*img;
	char	*addr;
	char	type;
    int     iterations;
    double	zoom;
    double	x1;
    double  x2;
    double  y1;
    double  y2;
	int		bpp;
	int		ll;
	int		endian;
    int		*mouse_x;
    int		*mouse_y;
}               t_data;

#endif
