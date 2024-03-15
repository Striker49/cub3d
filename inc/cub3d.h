#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/inc/libft.h"
# include "colors.h"
# include <stdio.h>
# include <math.h>
# include <../MLX42/include/MLX42/MLX42.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

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

enum	e_Direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING
};

//parsing
void	init_struct(t_data *data);
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
int		init_mlx(t_data *data);
void	ft_hook(void *param);
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

void	ft_floor_sky(t_data *data);
int		get_rgba(int r, int g, int b, int a);
int		ft_check_frame(t_data *data);
void	ft_gradient(t_data *data, int y, int x);

#endif