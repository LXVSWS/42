/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:50:48 by lwyss             #+#    #+#             */
/*   Updated: 2022/06/22 04:18:14 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//# include <mlx.h>
# include "mlx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define W 750
# define H 800

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	char	**map;
	char	*starting_pos;
	char	direction;
	int		max_map_x;
	int		max_map_y;
	int		block_size_x;
	int		block_size_y;
	int		player_x;
	int		player_y;
	int		x;
	int		y;
}				t_data;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

unsigned int	rgb2int(t_rgb rgb);
void			pixel_put(t_data *data, int x, int y, t_rgb rgb);
void			draw_element(t_data *data, int pos_x, int pos_y, t_rgb color);
void			init_player(t_data *data, int x, int y, t_rgb color_void);
void			draw_map(t_data *data, t_rgb color_wall, t_rgb color_void);

int				file_read(char **av);
int				file_size(int fd);
char			*file_copy(int fd, int size);
void			check_incorrect_input(t_data *data, char c);
void			check_map(t_data *data, char *file);

t_data			init(void);
t_rgb			rgb(unsigned char r, unsigned char g, unsigned char b);
int				ft_strlen(char *s);
void			error(char *s);

char			*strdupmod(char *s);
int				check_file(t_data *data, char *file);
int				detect_map(char *file, int i);
void			malloc_map(t_data *data);
void			full_free(t_data *data);

#endif
