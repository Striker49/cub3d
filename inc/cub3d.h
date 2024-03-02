#ifndef CUB3D_H
#define CUB3D_H
#include "../libft/inc/libft.h"
#include <stdio.h>

typedef struct s_data
{
	char	**map;
	int		map_size;
	char	*so;
	char	*no;
	char	*ea;
	char	*we;
}t_data;

void	ft_file_format(int argc, char *file);
int		ft_read_file(t_data *data, char **argv);
int valid(char **file, t_data *data);

int		errmessage(int a);
void	ft_free(t_data *data);
void	ft_print_map(char **s);


#endif