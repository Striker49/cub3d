#include "cub3d.h"

void ft_set_camera(t_data *data)
{
	t_vec vec;

	//position player
	data->pl_x = data->player.x;
	data->pl_y = data->player.y;
	//definir le vecteur directionnel
	data->pl_dir_x = -1;
	data->pl_dir_y = 0;
	//definir le vecteur normal
	vec.x = -data->pl_dir_y;
	vec.y = data->pl_dir_x;
	printf("Camera vector: (%f, %f)\n", vec.x, vec.y);

	//calcul du FOV horizontal
	data->fov_x = atan2(vec.y, vec.x);
	//calcul du FOV vectical
	data->aspect_ratio = (double)WINDOW_WIDTH / WINDOW_HEIGHT;
	data->fov_y = 2 * atan(tan(data->fov_x / 2) / data->aspect_ratio);

	printf("FOV horizontal: %f degrees\n", data->fov_x * 180 / M_PI);
    printf("FOV vertical: %f degrees\n", data->fov_y * 180 / M_PI);
}