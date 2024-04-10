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
	if (!(data->img[2] = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return;
	}
	if (mlx_image_to_window(data->mlx, data->img[2], 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return;
	}
	data->img[2]->instances[0].z = data->miniMap_satus;
}

void	move(t_data *data, int dir)
{
	reset_player_minimap(data);
	if (dir == NORTH && data->map[(int)(data->player.y + (sin(data->player_angle) * SPEED))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (cos(data->player_angle) * SPEED))] != '1')
	{
		if (data->map[(int)(data->player.y + (sin(data->player_angle) * SPEED))][(int)data->player.x] != '1')
			data->player.x += cos(data->player_angle) * SPEED;
		if (data->map[(int)(data->player.y)][(int)(data->player.x + (cos(data->player_angle) * SPEED))] != '1')
			data->player.y += sin(data->player_angle) * SPEED;
	}
	// if (dir == NORTH)
	// {
    //   if(data->map[(int)(data->player.x + data->dirX * SPEED)][(int)(data->player.y)] != 1)
	//   	data->player.x += data->dirX * SPEED;
    //   if(data->map[(int)(data->player.x)][(int)(data->player.y + data->dirY * SPEED)] != 1)
	//   	data->player.y += data->dirY * SPEED;
	// }
	else if (dir == SOUTH && data->map[(int)(data->player.y + (sin(data->player_angle)* -1))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (cos(data->player_angle) * -SPEED))] != '1')
	{
		if (data->map[(int)(data->player.y + (sin(data->player_angle)* -SPEED))][(int)data->player.x] != '1')
			data->player.x += cos(data->player_angle) * -SPEED;
		if (data->map[(int)(data->player.y)][(int)(data->player.x + (cos(data->player_angle) * -SPEED))] != '1')
			data->player.y += sin(data->player_angle) * -SPEED;
	}
	// else if (dir == SOUTH)
	// {
    // 	if(data->map[(int)(data->player.x - data->dirX * SPEED)][(int)(data->player.y)] != 1)
	// 		data->player.x -= data->dirX * SPEED;
    // 	if(data->map[(int)(data->player.x)][(int)(data->player.y - data->dirY * SPEED)] != 1)
	// 		data->player.y -= data->dirY * SPEED;
	// }
	else if (dir == WEST && data->map[(int)(data->player.y + (cos(data->player_angle) * -SPEED))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (sin(data->player_angle) * SPEED))] != '1')
	{
		if (data->map[(int)(data->player.y + (cos(data->player_angle) * -SPEED))][(int)data->player.x] != '1' )
			data->player.x += sin(data->player_angle) * SPEED;
		if (data->map[(int)(data->player.y)][(int)(data->player.x + (sin(data->player_angle) * SPEED))] != '1')
			data->player.y += cos(data->player_angle) * -SPEED;
	}
	else if (dir == EAST && data->map[(int)(data->player.y + (cos(data->player_angle) * SPEED))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (sin(data->player_angle) * -SPEED))] != '1')
	{
		if (data->map[(int)(data->player.y + (cos(data->player_angle) * SPEED))][(int)data->player.x] != '1')
			data->player.x += sin(data->player_angle) * -SPEED;
		if (data->map[(int)(data->player.y)][(int)(data->player.x + (sin(data->player_angle) * -SPEED))] != '1')
			data->player.y += cos(data->player_angle) * SPEED;
	}
	draw_player(data, data->player.x * 10, data->player.y * 10, ft_pixel(0xDC, 0x14, 0x3C,0xFF));
}
