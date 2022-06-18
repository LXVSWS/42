/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:50:48 by lwyss             #+#    #+#             */
/*   Updated: 2022/06/18 03:10:28 by lwyss            ###   ########.fr       */
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

# define W 800
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
	int		max_map_x;
	int		max_map_y;
	int		block_size_x;
	int		block_size_y;
	int		player_x;
	int		player_y;
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
void			draw_bg(t_data *data, t_rgb color);
void			draw_grill(t_data *data, t_rgb color);

int				file_read(char **av);
int				file_size(int fd);
char			*file_copy(int fd, int size);
void			check_incorrect_character(char c);
void			check_file(t_data *data, char *file);

t_data			init(void);
t_rgb			rgb(unsigned char r, unsigned char g, unsigned char b);
int				ft_strlen(char *s);
void			error(char *s);
void			check_movement(t_data *data);

#endif
