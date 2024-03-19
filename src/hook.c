#include "cub3d.h"

void	move(t_data *data, int dir)
{
	if (dir == NORTH && data->map[data->player.y - 1][data->player.x] != '1')
	{
		data->player.y -= 1;
		printf("move right\n");

	}
	else if (dir == SOUTH && data->map[data->player.y + 1][data->player.x] != '1')
	{
		data->player.y += 1;
		printf("move right\n");

	}
	else if (dir == WEST && data->map[data->player.y][data->player.x - 1] != '1')
	{
		data->player.x -= 1;
		printf("move right\n");

	}
	else if (dir == EAST && data->map[data->player.y][data->player.x + 1] != '1')
	{
		data->player.x += 1;
		printf("move right\n");
	}	
	ft_put_pixel(data);
}

void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
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
