#include "cub3d.h"

void    ft_rayon(t_data *data, t_ray *ray)
{
    data->dirX = data->pl_dir_x + data->planeX;
	data->dirY = data->pl_dir_y + data->planeY;
	ray->mapX = (int)data->player.x;
	ray->mapY = (int)data->player.y;

	//Direction du rayon
	data->cameraX = 2 * ray->line->x / (double)WINDOW_WIDTH - 1;
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
			ray->line->y0 = 0;
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
	int y;
	int buf_x;

	buf_x = 0;
	y = line->y0;
	while (y < line->y1 && line->y1 < WINDOW_HEIGHT && line->y0 >= 0)
	{
        if (data->ray->side == 1)
		{
			buf_x = get_hit(data, data->tex_Wall_N);
			// ft_get_texture(data, line, data->n_buf, buf_x);
            mlx_put_pixel(data->img[0], line->x, y, get_rgba(220, 237, 200, 255));
		}
		    // mlx_put_pixel(data->img[0], line->x, y, get_rgba(27, 94, 32, 255));
        else if (data->ray->side == 2)
            mlx_put_pixel(data->img[0], line->x, y, get_rgba(197, 225, 165, 255));
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(46, 125, 50, 255));
        else if (data->ray->side == 3)
            mlx_put_pixel(data->img[0], line->x, y, get_rgba(0, 237, 200, 255));
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(46, 125, 50, 255));
	    else
            mlx_put_pixel(data->img[0], line->x, y, get_rgba(197, 0, 165, 255));
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(27, 94, 32, 255));
		data->pixPosY = 0;
		y++;
	}
}

// t_data	get_data(void)
// {
// 	static mlx_t		mlx;
// 	static t_data		data;
// 	static mlx_texture_t	tex_Wall_R;

// 	data.mlx = &mlx;
// 	data.tex_Wall_R = &tex_Wall_R;
// 	return (data);
// }

static uint32_t **ft_buf_line_text(mlx_texture_t	*tex_Wall_R)
{
	int x;
	int y;
	int i;
	uint32_t **buf;

	x = 0;
	y = 0;
	i = 0;
	buf = malloc(sizeof(uint32_t *) * (TEX_HEIGHT + 1));
	while (y < TEX_HEIGHT)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			buf[x] = malloc(sizeof(uint32_t) * (TEX_WIDTH));
			buf[y][x] = get_rgba((uint32_t)tex_Wall_R->pixels[i], (uint32_t)tex_Wall_R->pixels[i + 1], (uint32_t)tex_Wall_R->pixels[i + 2], (uint32_t)tex_Wall_R->pixels[i + 3]);
			i += 4;
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

	hit = 0;
	if(data->ray->side == 4 || data->ray->side == 2)
		hit = data->ray->line->y + data->ray->perpWallDist * data->ray->rayDirY;
	else
		hit = data->ray->line->x + data->ray->perpWallDist * data->ray->rayDirX;
	hit -= (int)hit;
	buf_x = (int)(hit * (double)TEX_WIDTH);
	if ((data->ray->side == 4 || data->ray->side == 2) && data->ray->rayDirX > 0)
		buf_x = TEX_WIDTH - buf_x - 1;
	if ((data->ray->side == 1 || data->ray->side == 3) && data->ray->rayDirY < 0)
		buf_x = TEX_WIDTH - buf_x - 1;
	return (buf_x);
}

void	ft_get_texture(t_data *data, t_line *line, uint32_t **buf, int buf_x)
{
	double dist;
	double pos;
	int buf_y;
	int j;
	// t_data *data;

	// data = get_data();
	dist = 1.0 * TEX_HEIGHT / data->ray->h_wall;
	pos = ((double)line->y0 - (double)WINDOW_HEIGHT / 2 + (double)data->ray->h_wall / 2) * dist;
	if (pos < 0)
		pos = 0;
	j = line->y0;
	while (j < line->y1)
	{
		buf_y = (int)pos;
		if (pos > TEX_HEIGHT - 1)
			pos = TEX_HEIGHT - 1;
		pos += dist;
		mlx_put_pixel(data->img[0], line->x, j, buf[buf_y][buf_x]);
		j++;
	}
}

void	ft_load_texture(t_data *data)
{
	data->tex_Wall_N = mlx_load_png("/Users/kfortin/Documents/project_42/cub3d_kitty/wallTexture/Green_100/tex_G_100_01.png");
	if (data->tex_Wall_N == NULL)
		perror("Erreur lors du chargement de la texture");
	data->tex_Wall_S = mlx_load_png("/Users/kfortin/Documents/project_42/cub3d_kitty/wallTexture/Green_100/tex_G_100_02.png");
	if (data->tex_Wall_S == NULL)
		perror("Erreur lors du chargement de la texture");
	data->tex_Wall_E = mlx_load_png("/Users/kfortin/Documents/project_42/cub3d_kitty/wallTexture/Green_100/tex_G_100_03.png");
	if (data->tex_Wall_E == NULL)
		perror("Erreur lors du chargement de la texture");
	data->tex_Wall_O = mlx_load_png("/Users/kfortin/Documents/project_42/cub3d_kitty/wallTexture/Green_100/tex_G_100_03.png");
	if (data->tex_Wall_O == NULL)
		perror("Erreur lors du chargement de la texture");

	data->n_buf = ft_buf_line_text(data->tex_Wall_N);
	data->n_buf = ft_buf_line_text(data->tex_Wall_S);
	data->n_buf = ft_buf_line_text(data->tex_Wall_E);
	data->n_buf = ft_buf_line_text(data->tex_Wall_O);
}