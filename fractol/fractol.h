#ifndef FRACTOL_H
# define FRACTOL_H

#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_data
{
    void    *mlx;
    void    *win;
	void	*img;
	char	*addr;
    int     iterations;
    int     zoom;
    float   x1;
    float   x2;
    float   y1;
    float   y2;
    float   x_max;
    float   y_max;
	int		bpp; // bits per pixel
	int		ll;	// line length
	int		endian;
}               t_data;

#endif
