#include "cub3d.h"

int	init_mlx(t_data *data)
{
	int i;

	i = 0;
	// dprintf(2, "data->mlx: %p\n", &data->mlx);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", false);
	// dprintf(2, "OK\n");
	if (!data->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		ft_free(data);
		return(EXIT_FAILURE);
	}
	while (i < 3)
	{
		if (!(data->img[i] = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT)))
		{
			mlx_close_window(data->mlx);
			puts(mlx_strerror(mlx_errno));
			return(EXIT_FAILURE);
		}
		if (mlx_image_to_window(data->mlx, data->img[i], 0, 0) == -1)
		{
			mlx_close_window(data->mlx);
			puts(mlx_strerror(mlx_errno));
			return(EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}
