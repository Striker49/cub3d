#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_gradient(t_data *data, int y, int x)
{
	int color1[3] = {199, 0, 57};
	int color2[3] = {218, 247, 166};
	int	mix_color[3];
	double t;

	t = (double)y / WINDOW_HEIGHT;
	mix_color[0] = (int)((1 - t) * color1[0] + t * color2[0]);
	mix_color[1] = (int)((1 - t) * color1[1] + t * color2[1]);
	mix_color[2] = (int)((1 - t) * color1[2] + t * color2[2]);
	mlx_put_pixel(data->img, x, y, get_rgba(mix_color[0], mix_color[1], mix_color[2], 255));
}

int	ft_check_frame(t_data *data)
{
	if (data->sc_x <= WINDOW_WIDTH && data->sc_y <= WINDOW_HEIGHT && data->sc_y >= 0 && data->sc_x >= 0)
	{
		return (0);
	}
	return (1);
}

void	ft_floor_sky(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			ft_gradient(data, y, x);
			x++;
		}
		y++;
	}
}