#ifndef FRACTOL_H
# define FRACTOL_H

#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_struct
{
    void    *mlx;
    void    *win;
    int     iterations;
    int     zoom;
    float   x1;
    float   x2;
    float   y1;
    float   y2;
    float   x_max;
    float   y_max;
}               t_struct;

#endif