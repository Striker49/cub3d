#include "cub3d.h"

void	rotate_left(t_data *data, int32_t x)
{
	data->player_angle += x * 0.001;
	if (data->player_angle < 0)
		data->player_angle += ft_deg_rad(360);
	data->pl_dir_x = cos(data->player_angle) * 4;
	data->pl_dir_y = sin(data->player_angle) * 4;
}

void	rotate_right(t_data *data, int32_t x)
{
	data->player_angle += x * 0.001;
	if (data->player_angle > ft_deg_rad(360))
		data->player_angle -= ft_deg_rad(360);
	data->pl_dir_x = cos(data->player_angle) * 4;
	data->pl_dir_y = sin(data->player_angle) * 4;
}	

// void rotate(t_data *data, int32_t x, int direction)
// {
//     // Adjust angle based on direction and input x
//     data->player_angle += x * 0.001 * direction;

//     // Normalize the angle to be within the range [0, 2π]
//     while (data->player_angle >= 2 * M_PI) data->player_angle -= 2 * M_PI;
//     while (data->player_angle < 0) data->player_angle += 2 * M_PI;

//     // Update player's direction based on the new angle
//     data->pl_dir_x = cos(data->player_angle) * 2;
//     data->pl_dir_y = sin(data->player_angle) * 2;
// }

// void rotate_left(t_data *data, int32_t x)
// {
//     rotate(data, x, 1);  // Rotate left with positive direction
// }

// void rotate_right(t_data *data, int32_t x)
// {
//     rotate(data, x, -1);  // Rotate right with negative direction
// }

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
