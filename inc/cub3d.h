#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/inc/libft.h"
# include "colors.h"
# include <stdio.h>
# include <math.h>
# include <../MLX42/include/MLX42/MLX42.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define HALF_WINDOW_HEIGHT 540
# define WIN_WIDTH_MINUS 1920 - 1

# define PI 3.1415926535
# define TEX_WIDTH 100
# define TEX_HEIGHT 100
# define SPEED 0.5
// # define SIZE_IMG 128

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
	double wall_x;
	double	tex_height;
	double	tex_length;
}	t_line;

typedef struct s_ray
{
	int			side;
	double 		perpWallDist;
	double 		perpWallDist2;
	double rayDirX;
	double rayDirY;
	double deltaDistX;
	double deltaDistY;
	double sideDistX;
	double sideDistY;
	int			curr_x;
	int mapX;
	int mapY;
	int stepX;
	int stepY;
	int draw_start;
	int draw_end;
	// int line_height;
	int h_wall;
	t_line		*line;
} t_ray;

typedef struct s_data
{
	char			**map;
	char			**file;
	int				file_size;
	int				facing;
	int				height;
	int				width;
	char			*path[6];
	int				floor[3];
	int				ceiling[3];
	int				miniMap_satus;

	int i;
	int j;
	int c;
	char *temp;

	int pl_x;
	int pl_y;
	double pl_dir_x;
	double pl_dir_y;
	double planeX;
	double planeY;
	double dirX;
	double dirY;
	double cameraX;
	double fov_x;
	double fov_y;
	double aspect_ratio;
	double player_angle;
	int32_t	cursor_x;
	int32_t	cursor_y;

	t_vec			player;

	int		m;
	int		len;
	int		count;
	char	*tmp;

	mlx_texture_t	*tex_Wall_N;
	mlx_texture_t	*tex_Wall_S;
	mlx_texture_t	*tex_Wall_E;
	mlx_texture_t	*tex_Wall_O;
	uint32_t **n_buf;
	uint32_t **s_buf;
	uint32_t **e_buf;
	uint32_t **o_buf;
	float	x_ratio;
	float	y_ratio;
	int		src_x;
	int		src_y;
	int q;
	int w;
	int e;

	mlx_image_t		*img[4];
	mlx_t			*mlx;
	t_ray			*ray;
}	t_data;

// typedef	struct s_color
// {
// 	int Color1[3];
// 	int Color2[3];
// 	int pixTex[3];
// } t_color;

//parsing
void	init_struct(t_data *data);
void	init_ray(t_ray *ray);
void	ft_init_cam(t_data *data);
void	init_line(t_line *line);
void    ft_reinit_var(t_data *data);
void	clean_data(t_data *data);
void	clean_line(t_line *line);
void	clean_ray(t_ray *ray);
void	ft_file_format(int argc, char *file);
int		ft_read_file(t_data *data, char **argv);
int		check_info(char *file, int j, t_data *data);
char	*trim_spaces(t_data *data, char *s, char k);
int		extract_path(char *file, int j, t_data *data);
int		extract_color(char *file, int j, t_data *data);
char	*insert_path(char *direction, char *path, char *path_name);
void	find_col_len(char *file, int *i, int *j);
int		paths_colors(t_data *data);
void	extract_map(t_data *data, int i, int j);
int		valid(char **file, t_data *data);
int		ver_data(t_data *data);
int	ver_color(char *str, t_data *data);
int		pre_flood(t_data *data);
int		parse_map(t_data *data, char **map);
char	**ft_copy_map(char **map);
void	reset_player_minimap(t_data *data);
int		init_mlx(t_data *data);
void	move(t_data *data, int dir);
void 	move_1(t_data *data, int dir);
void 	move_2(t_data *data, int dir);
void 	move_3(t_data *data, int dir);
void 	move_4(t_data *data, int dir);
void	ft_hook(void *param);
void	mouse_hook(void *param);
// void	ft_displayMiniMap(t_data *data);
void	ft_option(mlx_key_data_t	keydata, void *param);

void	rotate_left(t_data *data, int32_t x);
void	rotate_right(t_data *data, int32_t x);

//free
void	ft_free(t_data *data);
void	free_close(int fd, t_data *data);
void	free_map(char **map);
//utils
int		errmessage(int a, char *s);
void	errmessage_2(int a, char *s);
void	errmessage_3(int a, char *s);
void	error_texture(t_data *data);
int 	ft_exit_failure(t_data *data);
void 	ft_exit_failure_2(t_data *data);
void 	ft_exit_failure_3(t_data *data);
int		ft_empty_file(char **file);
int		ft_iswhitesp(char c);
void	printmess(int fd, char *s);
int		ft_height(char **map);
void	ft_print_map(char **s);
int		ft_strchr_x(char **s, int c);
int		ft_strchr_y(char **s, int c);
int		ft_find_width(int i, int j, t_data *data);

void 	ft_dda(t_data *data, t_ray *ray);
void    ft_rayon(t_data *data, t_ray *ray);
void 	ft_setup(t_data *data, t_ray *ray);
void 	ft_forward_until_hit(t_ray *ray);
void	ft_trace_wall(t_data *data, t_ray *ray);
void	trace_line(t_data *data, t_line *line);
double	ft_deg_rad(int deg);
void	ft_floor_sky(t_data *data);
int		get_rgba(int r, int g, int b, int a);

void				ft_load_texture(t_data *data);
void	ft_fill_bufs(t_data *data);
uint32_t		**ft_buf_line_text(mlx_texture_t	*tex_Wall_R);
void	ft_get_texture(t_data *data, t_line *line, uint32_t **buf, int buf_x);
int get_hit(t_data *data, mlx_texture_t	*tex_Wall);
int get_hit2(t_data *data, mlx_texture_t	*tex_Wall);
uint32_t **ft_resize_tex(t_data *data, mlx_texture_t *tex_Wall, uint32_t **dest_data);

void ft_safety_small(uint32_t	**buf, int y);
void ft_safety(uint32_t	**buf);

int ft_check_oversize_tex(t_data *data);
int		ft_check_frame(int x, int y);
void	ft_gradient(t_data *data, int y, int x);

void	ft_put_pixel(void* param);

void	re_img(t_data *data);
void	draw_player(t_data *data, int32_t i, int32_t y, int32_t color);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
#endif