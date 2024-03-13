#include "cub3d.h"

void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->img[0]->instances[0].y -= 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->img[0]->instances[0].y += 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->img[0]->instances[0].x -= 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->img[0]->instances[0].x += 1;
}
