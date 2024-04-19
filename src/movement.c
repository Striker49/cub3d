#include "cub3d.h"

void	rotate_right(t_data *data, int32_t x)
{
	(void)x;
	double old_dirx;
	double old_planex;

	old_dirx = data->dirx;
	old_planex = data->planex;
	data->dirx = data->dirx * cos(-0.015) - data->diry * sin(-0.015);
	data->diry = old_dirx * sin(-0.015) + data->diry * cos(-0.015);
	data->planex = data->planex * cos(-0.015) - data->planey * sin(-0.015);
	data->planey = old_planex * sin(-0.015) + data->planey * cos(-0.015);

}

void	rotate_left(t_data *data, int32_t x)
{
	(void)x;
	double old_dirx;
	double old_planex;

	old_dirx = data->dirx;
	old_planex = data->planex;
	data->dirx = data->dirx * cos(0.015) - data->diry * sin(0.015);
	data->diry = old_dirx * sin(0.015) + data->diry * cos(0.015);
	data->planex = data->planex * cos(0.015) - data->planey * sin(0.015);
	data->planey = old_planex * sin(0.015) + data->planey * cos(0.015);
}

void	reset_player_minimap(t_data *data)
{
	mlx_delete_image(data->mlx, data->img[2]);
	data->img[2] = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!(data->img[2]))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return ;
	}
	if (mlx_image_to_window(data->mlx, data->img[2], 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return ;
	}
	data->img[2]->instances[0].z = data->minimap_satus;
}
