#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/inc/libft.h"
# include "colors.h"
# include <stdio.h>
# include <math.h>
# include <../MLX42/include/MLX42/MLX42.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define TEX_WIDTH 100
# define TEX_HEIGHT 100

enum	e_Direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING
};

typedef struct s_vec
{
	double x;
    double y;
}t_vec;

typedef struct s_data
{
	char			**map;
	char			**file;
	int				file_size;
	int				facing;
	int				height;
	int				width;
	char			**path;
	char	*floor;
	char	*ceiling;

	int sc_x;
	int sc_y;
	int pl_x;
	int pl_y;
	
	int pl_dir_x;
	int pl_dir_y;

	double fov_x;
	double fov_y;
	double aspect_ratio;

	mlx_image_t		*img;
	mlx_t			*mlx;
}	t_data;

typedef	struct s_line
{
	int x;
	int x0;
	int x1;
	int y;
	int y0;
	int y1;
	int tex_x;
	int tex_y;
}	t_line;

typedef struct s_ray
{
	int			side;
	double 		perpWallDist;
	double rayDirX;
	double rayDirY;
	int			curr_x;
	int mapX;
	int mapY;
	int draw_start;
	int draw_end;
	int line_height;
	int h_wall;
	t_line		*line;
} t_ray;

typedef	struct s_color
{
	int Color1[3];
	int Color2[3];
} t_color;

//parsing
void	init_struct(t_data *data);
void	init_ray(t_ray *ray);
void	init_line(t_line *line);
void	ft_file_format(int argc, char *file);
int		ft_read_file(t_data *data, char **argv);
int		check_info(char *file, int j, t_data *data);
int		extract_path(char *file, int j, t_data *data);
int		paths_colors(t_data *data);
void	extract_map(t_data *data, int i, int j);
int		valid(char **file, t_data *data);
int		ver_data(t_data *data);
int		pre_flood(t_data *data);
int		parse_map(t_data *data, char **map);
//mlx
// int		init_mlx(t_data *data);
// void	ft_hook(void *param);
//free
void	ft_free(t_data *data);
void	free_close(int fd, t_data *data);
void	free_map(char **map);
//utils
int		errmessage(int a, char *s);
int		ft_empty_file(char **file);
int		ft_iswhitesp(char c);
void	printmess(int fd, char *s);
int		ft_height(char **map);
void	ft_print_map(char **s);
int		ft_strchr_x(char **s, int c);
int		ft_strchr_y(char **s, int c);

void 	ft_set_camera(t_data *data);
void 	ft_DDA(t_data *data, t_ray *ray);
void	ft_trace_wall(t_data *data, t_ray *ray);
void	trace_line(t_data *data, t_line *line);
double	ft_deg_rad(int deg);
// void	ft_scaling_transform(t_data *data, t_ray *ray);
void	ft_floor_sky(t_data *data);
int		get_rgba(int r, int g, int b, int a);
void	paint_line(t_data *data, t_line *line, t_color *color);
void	paint_texture_line(t_data *data, t_ray *ray, t_line *line, double wall_x);

int		ft_check_frame(t_data *data);
void	ft_gradient(t_data *data, int y, int x);

#endif