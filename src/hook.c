#include "cub3d.h"

void	rotate_left(t_data *data)
{
	data->player_angle -= 0.1;
	if (data->player_angle < 0)
		data->player_angle += 2 * PI;
	data->pl_dir_x = cos(data->player_angle) * 5;
	data->pl_dir_y = sin(data->player_angle) * 5;
}

void	rotate_right(t_data *data)
{
	data->player_angle += 0.1;
	if (data->player_angle > 2 * PI)
		data->player_angle -= 2 * PI;
	data->pl_dir_x = cos(data->player_angle) * 5;
	data->pl_dir_y = sin(data->player_angle) * 5;
}

void	move(t_data *data, int dir)
{
	if (dir == NORTH && data->map[(int)(data->player.y + (data->pl_dir_y * 0.1))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (data->pl_dir_x * 0.1))] != '1')
	{
		data->player.x += data->pl_dir_x * 0.1;
		data->player.y += data->pl_dir_y * 0.1;
		data->img[2]->instances[0].x += data->pl_dir_x * 1;
		data->img[2]->instances[0].y += data->pl_dir_y * 1;
	}
	else if (dir == SOUTH && data->map[(int)(data->player.y - (data->pl_dir_y * 0.1))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x - (data->pl_dir_x * 0.1))] != '1')
	{
		data->player.x -= data->pl_dir_x * 0.1;
		data->player.y -= data->pl_dir_y * 0.1;
		data->img[2]->instances[0].x -= data->pl_dir_x * 1;
		data->img[2]->instances[0].y -= data->pl_dir_y * 1;
	}
	else if (dir == WEST)
		rotate_left(data);
	else if (dir == EAST)
		rotate_right(data);
	// ft_put_pixel(data);
}

void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		// ft_free(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		move(data, NORTH);
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		move(data, SOUTH);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		move(data, WEST);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		move(data, EAST);

}
