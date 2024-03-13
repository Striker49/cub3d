#include "cub3d.h"

int	init_mlx(t_data *data)
{
	if (!(data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "MLX42", true)))
	{
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	return (0);
}
