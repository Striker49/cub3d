#include "cub3d.h"

void	move(t_data *data, int dir)
{
	reset_player_minimap(data);
	if (dir == NORTH && data->map[(int)(data->player.y + (sin(data->player_angle) * SPEED))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (cos(data->player_angle) * SPEED))] != '1')
		move_1(data, dir);
	else if (dir == SOUTH && data->map[(int)(data->player.y + (sin(data->player_angle)* -1))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (cos(data->player_angle) * -SPEED))] != '1')
		move_2(data, dir);
	else if (dir == WEST && data->map[(int)(data->player.y + (cos(data->player_angle) * -SPEED))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (sin(data->player_angle) * SPEED))] != '1')
		move_3(data, dir);
	else if (dir == EAST && data->map[(int)(data->player.y + (cos(data->player_angle) * SPEED))][(int)data->player.x] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + (sin(data->player_angle) * -SPEED))] != '1')
		move_4(data, dir);
	draw_player(data, data->player.x * 10, data->player.y * 10, ft_pixel(0xDC, 0x14, 0x3C,0xFF));
}

void 	move_1(t_data *data, int dir)
{
	(void)dir;
	if (data->map[(int)(data->player.y + (sin(data->player_angle) * SPEED))][(int)data->player.x] != '1')
		data->player.x += cos(data->player_angle) * SPEED;
	if (data->map[(int)(data->player.y)][(int)(data->player.x + (cos(data->player_angle) * SPEED))] != '1')
		data->player.y += sin(data->player_angle) * SPEED;
}

void 	move_2(t_data *data, int dir)
{
	(void)dir;
	if (data->map[(int)(data->player.y + (sin(data->player_angle)* -SPEED))][(int)data->player.x] != '1')
		data->player.x += cos(data->player_angle) * -SPEED;
	if (data->map[(int)(data->player.y)][(int)(data->player.x + (cos(data->player_angle) * -SPEED))] != '1')
		data->player.y += sin(data->player_angle) * -SPEED;
}

void 	move_3(t_data *data, int dir)
{
	(void)dir;
	if (data->map[(int)(data->player.y + (cos(data->player_angle) * -SPEED))][(int)data->player.x] != '1' )
		data->player.x += sin(data->player_angle) * SPEED;
	if (data->map[(int)(data->player.y)][(int)(data->player.x + (sin(data->player_angle) * SPEED))] != '1')
		data->player.y += cos(data->player_angle) * -SPEED;
}

void 	move_4(t_data *data, int dir)
{
	(void)dir;
	if (data->map[(int)(data->player.y + (cos(data->player_angle) * SPEED))][(int)data->player.x] != '1')
		data->player.x += sin(data->player_angle) * -SPEED;
	if (data->map[(int)(data->player.y)][(int)(data->player.x + (sin(data->player_angle) * -SPEED))] != '1')
		data->player.y += cos(data->player_angle) * SPEED;
}