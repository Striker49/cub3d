#ifndef CUB3D_H
#define CUB3D_H
# include "../libft/inc/libft.h"
# include "colors.h"
# include <stdio.h>
# include <math.h>
# include <../MLX42/include/MLX42/MLX42.h>

# define WINDOW_WIDTH 2000
# define WINDOW_HEIGHT 1180

typedef struct s_vec
{
	double x;
    double y;
}t_vec;

typedef struct s_data
{
	char	**map;
	char	**file;
	int		file_size;
	char	*so;
	char	*no;
	char	*ea;
	char	*we;
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
}t_data;

void	init_struct(t_data *data);
void	ft_file_format(int argc, char *file);
int		ft_read_file(t_data *data, char **argv);
int		check_info(char *file, int j, t_data *data);
int 	paths_colors(t_data *data);
void	extract_map(t_data *data, int i, int j);
int		valid(char **file, t_data *data);

int		ver_data(t_data *data);

int		errmessage(int a, char *s);
int		ft_iswhitesp(char c);
void	ft_free(t_data *data);
void	free_close(int fd, t_data *data);
void	printmess(int fd, char *s);
void	ft_print_map(char **s);

void ft_set_camera(t_data *data);
void	ft_floor_sky(t_data *data);
int	get_rgba(int r, int g, int b, int a);
int	ft_check_frame(t_data *data);

#endif