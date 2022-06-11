#ifndef CUB3D_H
# define CUB3D_H

//# include <mlx.h>
# include "mlx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define W 800
# define H 800

typedef struct	s_data
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int	bpp;
	int	ll;
	int	endian;
	char *map;
	int	block_size;
	int	player_x;
	int	player_y;
}				t_data;

typedef struct	s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_rgb;

int				ft_strlen(char *s);
void			check_map(char **av);
int				map_read(char **av);
int				map_size(int map_fd);
char			*map_copy(int map_fd, int size);

t_data			init(char **av);
unsigned int	rgb2int(t_rgb rgb);
t_rgb			rgb(unsigned char r, unsigned char g, unsigned char b);
void			pixel_put(t_data *data, int x, int y, t_rgb rgb);

#endif
