#include "cub3d.h"
#include <fcntl.h>

void	ft_file_format(int argc, char *file)
{
	int		i;
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
		errmessage(6, file);
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
	if (ft_empty_file(data->file) == 1)
		errmessage(15, NULL);
	if (data->file_size != i)
		return (free_close(fd, data), 1);
	if (fd == -1)
		return (free_close(fd, data), 1);
	return (0);
}

int	ft_read_file(t_data *data, char **argv)
{
	int		fd;
	int		i;
	char	*rd;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_free(data);
		exit(1);
	}
	while (fd > 0)
	{
		rd = get_next_line(fd);
		if ((int)ft_strlen(rd) > data->width)
			data->width = ft_strlen(rd);
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
	return (0);
}

int	paths_colors(t_data *data)
{
	if (!data->path[NORTH] || !data->path[SOUTH] || !data->path[EAST]
		|| !data->path[WEST] || !data->path[FLOOR] || !data->path[CEILING])
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
			if (file[i][j] != ' ' && file[i][j] != '	' && file[i][j] != '\n'
					&& file[i][j] != 0)
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
	// replace_spaces(data);
	if (data->map[0] == 0)
		errmessage(10, NULL);
	return (0);
}
