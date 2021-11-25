#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 1000
# define HEIGHT 1000

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
    float   zoom;
    float   x1;
    float   x2;
    float   y1;
    float   y2;
    int     x_max;
    int     y_max;
	int		bpp; // bits per pixel
	int		ll;	// line length
	int		endian;
}               t_data;

#endif
