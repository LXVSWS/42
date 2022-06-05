#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define W 500
# define H 500

typedef struct	s_data
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int	bpp;
	int	ll;
	int	endian;
	int	x;
	int	y;
}				t_data;

typedef struct	s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}				t_rgb;

t_data			init();
unsigned int	rgb2int(t_rgb rgb);
t_rgb			rgb(unsigned char r, unsigned char g, unsigned char b);
void			pixel_put(t_data *data, int x, int y, t_rgb rgb);

#endif
