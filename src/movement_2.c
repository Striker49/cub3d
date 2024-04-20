#include "cub3d.h"

void	move(t_data *data, int dir)
{
	set_player_angle(data);
	reset_player_minimap(data);
	if (dir == NORTH)
		move_1(data);
	else if (dir == SOUTH)
		move_2(data);
	else if (dir == WEST)
		move_3(data);
	else if (dir == EAST)
		move_4(data);
	draw_player(data, data->player.x * 10, data->player.y
		* 10, ft_pixel(0xDC, 0x14, 0x3C, 0xFF));
}

void	move_1(t_data *data)
{
	if (data->map[(int)(data->player.y + (data->diry * SPEED))]
		[(int)data->player.x] != '1')
		data->player.y += data->diry * SPEED;
	if (data->map[(int)(data->player.y)][(int)((data->player.x) + (data->dirx * SPEED))] != '1')
		data->player.x += data->dirx * SPEED;
}

void	move_2(t_data *data)
{
	if (data->map[(int)(data->player.y - (data->diry * SPEED))]
		[(int)data->player.x] != '1')
		data->player.y -= data->diry * SPEED;
	if (data->map[(int)(data->player.y)][(int)((data->player.x) - (data->dirx * SPEED))] != '1')
		data->player.x -= data->dirx * SPEED;
}

void	move_3(t_data *data)
{
	if (data->map[(int)(data->player.y - (data->planey * SPEED))]
		[(int)data->player.x] != '1')
		data->player.y -= data->planey * SPEED;
	if (data->map[(int)(data->player.y)][(int)((data->player.x) - (data->planex * SPEED))] != '1')
		data->player.x -= data->planex * SPEED;
}

void	move_4(t_data *data)
{
	if (data->map[(int)(data->player.y + (data->planey * SPEED))]
		[(int)data->player.x] != '1')
		data->player.y += data->planey * SPEED;
	if (data->map[(int)(data->player.y)][(int)((data->player.x) + (data->planex * SPEED))] != '1')
		data->player.x += data->planex * SPEED;
}
