#include "cub3d.h"

void	rotate_left(t_data *data, int32_t x)
{
	data->player_angle -= x * 0.001;
	if (data->player_angle < 0)
		data->player_angle += 2 * PI;
	data->pl_dir_x = cos(data->player_angle) * 5;
	data->pl_dir_y = sin(data->player_angle) * 5;
}

void	rotate_right(t_data *data, int32_t x)
{
	data->player_angle += x * 0.001;
	if (data->player_angle > 2 * PI)
		data->player_angle -= 2 * PI;
	data->pl_dir_x = cos(data->player_angle) * 5;
	data->pl_dir_y = sin(data->player_angle) * 5;
}

void	move(t_data *data, int dir)
{
	if (dir == NORTH && data->map[(int)(data->player.y + (sin(data->player_angle) * 1))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (cos(data->player_angle) * 1))] != '1')
	{
		data->player.x += cos(data->player_angle);
		data->player.y += sin(data->player_angle);
		data->img[2]->instances[0].x += cos(data->player_angle) * 10;
		data->img[2]->instances[0].y += sin(data->player_angle) * 10;
		printf("data->player.x: %f\n", data->player.x);
		printf("data->player.y %f\n", data->player.y);
	}
	else if (dir == SOUTH && data->map[(int)(data->player.y + (sin(data->player_angle)* -1))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (cos(data->player_angle) * -1))] != '1')
	{
		data->player.x += cos(data->player_angle) * -1;
		data->player.y += sin(data->player_angle) * -1;
		data->img[2]->instances[0].x += cos(data->player_angle) * -10;
		data->img[2]->instances[0].y += sin(data->player_angle) * -10;
		printf("data->player.x: %f\n", data->player.x);
		printf("data->player.y: %f\n", data->player.y);
	}
	else if (dir == WEST && data->map[(int)(data->player.y + (cos(data->player_angle) * -1))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (sin(data->player_angle) * 1))] != '1')
	{
		data->player.x += sin(data->player_angle);
		data->player.y += cos(data->player_angle) * -1;
		data->img[2]->instances[0].x += sin(data->player_angle) * 10;
		data->img[2]->instances[0].y += cos(data->player_angle) * -10;
	}
	else if (dir == EAST && data->map[(int)(data->player.y + (cos(data->player_angle) * 1))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (sin(data->player_angle) * -1))] != '1')
	{
		data->player.x += sin(data->player_angle) * -1;
		data->player.y += cos(data->player_angle);
		data->img[2]->instances[0].x += sin(data->player_angle) * -10;
		data->img[2]->instances[0].y += cos(data->player_angle) * 10;
	}
}
