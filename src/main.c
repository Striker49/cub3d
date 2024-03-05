#include <stdio.h>
#include "cub3d.h"

int	main( int argc, char **argv)
{
	t_data data;

	init_struct(&data);
	ft_file_format(argc, argv[1]);
	ft_read_file(&data, argv);
	return (0);
}