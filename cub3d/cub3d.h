/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyss <lwyss@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:50:48 by lwyss             #+#    #+#             */
/*   Updated: 2023/01/07 14:57:01 by lwyss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# define W 800
# define H 800
# define PI 3.14159265
# define DR 0.01745329
# define FOV 60

typedef struct s_tex
{
	void	*no;
	int		no_w;
	int		no_h;
	char	*no_addr;
	int		no_bpp;
	int		no_ll;
	int		no_endian;
	void	*so;
	int		so_w;
	int		so_h;
	char	*so_addr;
	int		so_bpp;
	int		so_ll;
	int		so_endian;
	void	*we;
	int		we_w;
	int		we_h;
	char	*we_addr;
	int		we_bpp;
	int		we_ll;
	int		we_endian;
	void	*ea;
	int		ea_w;
	int		ea_h;
	char	*ea_addr;
	int		ea_bpp;
	int		ea_ll;
	int		ea_endian;
}	t_tex;

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
	t_tex	tex;
	char	**f;
	char	**c;
	char	**map;
	char	*starting_pos;
	char	direction;
	char	print_map;
	int		max_map_x;
	int		max_map_y;
	int		player_map_x;
	int		player_map_y;
	float	block_size_x;
	float	block_size_y;
	float	player_x;
	float	player_y;
	float	player_delta_x;
	float	player_delta_y;
	float	player_angle;
}				t_data;

typedef struct s_ray
{
	float	rx;
	float	ry;
	int		mx;
	int		my;
	float	wall_h;
	char	side;
	float	hit_x;
	float	hit_y;
	int		y_offset;
}	t_ray;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

unsigned int	rgb2int(t_rgb rgb);
void			pixel_put(t_data *data, int x, int y, t_rgb rgb);
void			draw_element(t_data *data, int pos_x, int pos_y, t_rgb color);
void			draw_player(t_data *data);
void			draw_rays(t_data *data, float angle);

int				draw(t_data *data);
void			draw_3d(t_data *data, t_ray *ray);
void			normal_view(t_data *data, t_ray ray, float offset, int *x);
void			close_view(t_data *data, t_ray ray, float offset, int *x);
void			draw_map(t_data *data);

int				file_read(char **av);
int				file_size(int fd);
char			*file_copy(int fd, int size);
void			check_incorrect_input(t_data *data, char c);
void			check_map(t_data *data, char *file);

char			**ft_split(char *s, char c);

void			init_textures(t_data *data);
unsigned int	north_side(t_data *data, t_ray *ray, int x, int y);
unsigned int	south_side(t_data *data, t_ray *ray, int x, int y);
unsigned int	east_side(t_data *data, t_ray *ray, int x, int y);
unsigned int	west_side(t_data *data, t_ray *ray, int x, int y);

t_data			init(void);
t_data			init2(t_data data);
t_rgb			rgb(unsigned char r, unsigned char g, unsigned char b);
int				strln(char *s);
void			error(char *s);

char			*strdupmod(char *s);
int				check_file(t_data *data, char *file);
int				detect_map(char *file, int i);
void			malloc_map(t_data *data);
void			full_free(t_data *data);

void			mapdup(t_data *data, char c, int *j, int *k);
void			copy_map(t_data *data, char *file);
void			init_player(t_data *data, int x, int y);
void			detect_player(t_data *data);
float			pythagore(t_data *data, float rx, float ry, float angle);

t_ray			raycasting(t_data *data, float angle);
void			init_textures_sides(t_data *data, t_ray *ray, float angle);
void			texturing(t_data *data, t_ray ray, int x, int y);
void			strafing(t_data *data, int keycode);
int				ft_atoi(const char *s);

t_rgb			uinttorgb(unsigned int i);
void			draw_floor(t_data *data, int x, int y);
void			rgb_sky_check(t_data *data);
void			rgb_floor_check(t_data *data);
int				clean_exit(t_data *data);

void			no_detected(t_data *data, char *file);
void			so_detected(t_data *data, char *file);
void			we_detected(t_data *data, char *file);
void			ea_detected(t_data *data, char *file);
void			f_detected(t_data *data, char *file);
void			c_detected(t_data *data, char *file);

#endif
