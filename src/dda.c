#include "cub3d.h"

void    ft_rayon(t_data *data, t_ray *ray)
{
    data->dirX = data->pl_dir_x + data->planeX;
	data->dirY = data->pl_dir_y + data->planeY;
	ray->mapX = (int)data->player.x;
	ray->mapY = (int)data->player.y;

	//Direction du rayon
	data->cameraX = 2 * ray->line->x / (double)WIN_WIDTH_MINUS - 1;
	ray->rayDirX = data->dirX + data->planeX * data->cameraX;
	ray->rayDirY = data->dirY + data->planeY * data->cameraX;

	//longueur du rayon
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);

    //direction du rayon passe en haut ou en bas du pi
	if(ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (data->player.x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - data->player.x) * ray->deltaDistX;
	}
	if(ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (data->player.y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - data->player.y) * ray->deltaDistY;
	}
}

void ft_DDA(t_data *data, t_ray *ray)
{
	int hit;
	// int side;

	hit = 0;
    ft_rayon(data, ray);

	//Digital Differential Analysis
	while (hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 4;
			if (ray->stepX == -1)
				ray->side = 2;

		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
			if (ray->stepY == -1)
				ray->side = 3;
		}
		if (ray->mapX >= 0 && ray->mapY <= data->height && data->map[(int)ray->mapY][(int)ray->mapX] == '1' )
			hit = 1;
	}

	//distance projected
	if (ray->side % 2 == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
}


double	ft_deg_rad(int deg)
{
	double	rad;

	rad = deg * M_PI / 180.0;
	return (rad);
}

void	ft_trace_wall(t_data *data, t_ray *ray)
{
	//trigonometrie pour trouver la hauteur du mur sur l'écran
	ray->line->tex_x = TEX_WIDTH;
	ray->line->x = 0;
	while (ray->line->x < WINDOW_WIDTH)
	{
		ft_DDA(data, ray);
		ray->h_wall = (int)(WINDOW_HEIGHT / ray->perpWallDist);
		ray->line->y0 = -ray->h_wall / 2 + WINDOW_HEIGHT / 2;
		if (ray->line->y0 < 0)
			ray->line->y0 += 0;
		ray->line->y1 = ray->h_wall / 2 + WINDOW_HEIGHT / 2;
		if (ray->line->y1 >= WINDOW_HEIGHT)
			ray->line->y1 = WINDOW_HEIGHT - 1;
		trace_line(data, ray->line);
		ray->line->x++;
		clean_data(data);
		clean_line(ray->line);
		// clean_ray(ray);
	}
}

void	trace_line(t_data *data, t_line *line)
{
	// int y;
	int buf_x;

	buf_x = 0;
	// y = line->y0;
	// while (y < line->y1 && line->y1 < WINDOW_HEIGHT && line->y0 >= 0)
	// {
        if (data->ray->side == 1)
		{
			buf_x = get_hit(data, data->tex_Wall_N);
			ft_get_texture(data, line, data->n_buf, buf_x);
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(220, 237, 200, 255));
		    // mlx_put_pixel(data->img[0], line->x, y, get_rgba(27, 94, 32, 255));
		}
        else if (data->ray->side == 2)
		{
			buf_x = get_hit2(data, data->tex_Wall_S);
			ft_get_texture(data, line, data->s_buf, buf_x);
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(197, 225, 165, 255));
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(46, 125, 50, 255));
		}
		else if (data->ray->side == 3)
		{
			buf_x = get_hit(data, data->tex_Wall_E);
			ft_get_texture(data, line, data->e_buf, buf_x);
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(220, 237, 200, 255));
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(46, 125, 50, 255));
		}
		else
		{
			buf_x = get_hit2(data, data->tex_Wall_O);
			ft_get_texture(data, line, data->o_buf, buf_x);
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(197, 225, 165, 255));
		}
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(27, 94, 32, 255));
	// 	y++;
	// }
}

static uint32_t **ft_buf_line_text(mlx_texture_t	*tex_Wall_R)
{
	int x;
	int y;
	int i;
	uint32_t **buf;

	x = 0;
	y = 0;
	i = 0;
	buf = malloc(sizeof(uint32_t *) * (TEX_HEIGHT));
	if (!buf)
	{
		//free
		return (NULL);
	}
	while (y < tex_Wall_R->height)
	{
		buf[y] = malloc(sizeof(uint32_t) * (TEX_WIDTH));
		if (!buf[y])
		{
			// ft_free();
			return (NULL);
		}
		x = 0;
		while (x < tex_Wall_R->width)
		{
			i = (y * tex_Wall_R->width * 4) + (x * 4);
			buf[y][x] = get_rgba(tex_Wall_R->pixels[i], tex_Wall_R->pixels[i + 1], tex_Wall_R->pixels[i + 2], tex_Wall_R->pixels[i + 3]);
			x++;
		}
		y++;
	}
	return (buf);
}

int get_hit(t_data *data, mlx_texture_t	*tex_Wall)
{
	double hit;
	int buf_x;

	hit = data->ray->perpWallDist;
	hit = data->player.x + hit * data->ray->rayDirX;
	hit -= floor(hit);
	buf_x = (int)(hit * (double)tex_Wall->width);
	return (buf_x);
}

int get_hit2(t_data *data, mlx_texture_t	*tex_Wall)
{
	double hit;
	int buf_x;

	hit = data->ray->perpWallDist;
	hit = data->player.y + hit * data->ray->rayDirY;
	hit -= floor(hit);
	buf_x = (int)(hit * (double)tex_Wall->width);
	return (buf_x);
}

void	ft_get_texture(t_data *data, t_line *line, uint32_t **buf, int buf_x)
{
	int buf_y;
	int j;
	float prop;

	j = line->y0;
	prop = ((float)TEX_WIDTH / data->ray->h_wall);
	while (j < line->y1)
	{
		buf_y = (j - line->y0) * prop;
		if (buf_y >= 0 && buf_y <= TEX_HEIGHT && buf_x >= 0 && buf_x <= TEX_WIDTH && ft_check_frame(line->x, j) == 0)
			mlx_put_pixel(data->img[0], line->x, j, buf[buf_y][buf_x]);
		j++;
	}
}

void error_texture(t_data *data)
{
	perror("Erreur lors du chargement de la texture");
	ft_free(data);
	exit(1);
}

void	ft_load_texture(t_data *data)
{
	data->tex_Wall_N = mlx_load_png(data->path[NORTH]);
	if (data->tex_Wall_N == NULL)
		error_texture(data);
	data->tex_Wall_S = mlx_load_png(data->path[SOUTH]);
	if (data->tex_Wall_S == NULL)
		error_texture(data);
	data->tex_Wall_E = mlx_load_png(data->path[EAST]);
	if (data->tex_Wall_E == NULL)
		error_texture(data);
	data->tex_Wall_O = mlx_load_png(data->path[WEST]);
	if (data->tex_Wall_O == NULL)
		error_texture(data);
	data->n_buf = ft_buf_line_text(data->tex_Wall_N);
	data->s_buf = ft_buf_line_text(data->tex_Wall_S);
	data->e_buf = ft_buf_line_text(data->tex_Wall_E);
	data->o_buf = ft_buf_line_text(data->tex_Wall_O);
}
