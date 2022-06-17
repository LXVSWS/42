#include "cub3d.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 13)
		data->player_y -= data->block_size_y;
	if (keycode == 0)
		data->player_x -= data->block_size_x;
	if (keycode == 1)
		data->player_y += data->block_size_y;
	if (keycode == 2)
		data->player_x += data->block_size_x;
	if (keycode == 53)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (data->player_x + data->block_size_x > W)
		data->player_x -= data->block_size_x;
	if (data->player_y + data->block_size_y > H)
		data->player_y -= data->block_size_y;
	if (data->player_x < 0)
		data->player_x += data->block_size_x;
	if (data->player_y < 0)
		data->player_y += data->block_size_y;
	draw_grill(data, rgb(114, 114, 114));
	draw_element(data, data->player_x, data->player_y, rgb(255, 255, 255));
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
	char	*file;

	if (ac == 2)
	{
		data = init();
		file = file_copy(file_read(av), file_size(file_read(av)));
		check_file(&data, file);
		free(file);
		draw_grill(&data, rgb(114, 114, 114));
		draw_element(&data, data.player_x, data.player_y, rgb(255, 255, 255));
		mlx_key_hook(data.win, key_hook, &data);
		mlx_loop(data.mlx);
	}
	else
		printf("Error\nArgument number invalid\n");
	return (0);
}
