#include "cub3d.h"

void	rotate_left(t_data *data, int32_t x)
{
	// (void)x;
	// double oldDirX = data->pl_dir_x;
	// data->pl_dir_x = data->pl_dir_x * cos(-ROTSPEED) - data->pl_dir_y * sin(-ROTSPEED);
	// data->pl_dir_y = oldDirX * sin(-ROTSPEED) + data->pl_dir_y * cos(-ROTSPEED);
	// double oldPlaneX = data->planeX;
	// data->planeX = data->planeX * cos(-ROTSPEED) - data->planeY * sin(-ROTSPEED);
	// data->planeY = oldPlaneX * sin(-ROTSPEED) + data->planeY * cos(-ROTSPEED);
	data->player_angle += x * 0.001;
	if (data->player_angle < 0)
		data->player_angle += ft_deg_rad(360);
	data->pl_dir_x = cos(data->player_angle) * 5;
	data->pl_dir_y = sin(data->player_angle) * 5;
}

void	rotate_right(t_data *data, int32_t x)
{
	// (void)x;
	// double oldDirX = data->pl_dir_x;
	// data->pl_dir_x = data->pl_dir_x * cos(ROTSPEED) - data->pl_dir_y * sin(ROTSPEED);
	// data->pl_dir_y = oldDirX * sin(ROTSPEED) + data->pl_dir_y * cos(ROTSPEED);
	// double oldPlaneX = data->planeX;
	// data->planeX = data->planeX * cos(ROTSPEED) - data->planeY * sin(ROTSPEED);
	// data->planeY = oldPlaneX * sin(ROTSPEED) + data->planeY * cos(ROTSPEED);
	data->player_angle += x * 0.001;
	if (data->player_angle > ft_deg_rad(360))
		data->player_angle -= ft_deg_rad(360);
	data->pl_dir_x = cos(data->player_angle) * 5;
	data->pl_dir_y = sin(data->player_angle) * 5;
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
	data->img[2]->instances[0].z = data->miniMap_satus;
}
