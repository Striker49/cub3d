#include "cub3d.h"
#include <fcntl.h>

void	ft_file_format(int argc, char *file)
{
	int		i;
	int		ext;
	char	*s;

	if (argc < 2)
		errmessage(8, NULL);
	if (argc > 2)
		errmessage(9, NULL);
	s = ".cub";
	i = ft_strlen(file);
	if (ft_strncmp(file + (i - 4), s, 4) != 0)
		errmessage(5, NULL);
	if (access(file, F_OK) != 0)
	{
		errmessage(6, file);
	}
}

int	ft_create_file(char **argv, t_data *data)
{
	int	fd;
	int	i;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (free_close(fd, data), 1);
	data->file = ft_calloc(data->file_size + 1, sizeof(*data->file));
	if (!data->file)
		return (free(data->file), 1);
	i = 0;
	while (fd > 0)
	{
		data->file[i] = get_next_line(fd);
		if (data->file[i] == NULL)
			break ;
		i++;
	}
	if (data->file_size != i)
		return (free_close(fd, data), 1);
	if (fd == -1)
		return (free_close(fd, data), 1);
	return (0);
}

int	ft_read_file(t_data *data, char **argv)
{
	int			fd;
	int			i;
	char		*rd;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(0);
	while (fd > 0)
	{
		rd = get_next_line(fd);
		if (rd == NULL)
			break ;
		i++;
		free(rd);
	}
	close(fd);
	data->file_size = i;
	if (ft_create_file(argv, data))
		return (1);
	valid(data->file, data);
	printf("NO:%s\n", data->no);
	printf("SO:%s\n", data->so);
	printf("WE:%s\n", data->we);
	printf("EA:%s\n", data->ea);
	printf("F:%s\n", data->floor);
	printf("C:%s\n", data->ceiling);
	printf("MAP:\n");
	ft_print_map(data->map);
	printf("\n\n");

	// ft_free(data);
	return (0);
}

int	paths_colors(t_data *data)
{
	if (!data->no || !data->so || !data->ea || !data->we \
		|| !data->floor || !data->ceiling)
		return (1);
	return (0);
}

int	valid(char **file, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] != ' ' && file[i][j] != '	' \
				&& file[i][j] != '\n' && file[i][j] != 0)
				j = check_info(file[i], j, data);
			j++;
		}
		i++;
		if (!paths_colors(data))
		{
			j = 0;
			break ;
		}
	}
	extract_map(data, i, j);
	if (data->map[0] == 0)
		errmessage(10, NULL);
	return (0);
}
