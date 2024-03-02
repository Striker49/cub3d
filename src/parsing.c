#include "cub3d.h"
#include <fcntl.h>

void	ft_file_format(int argc, char *file)
{
	int		i;
	int		ext;
	char	*s;

	if (argc < 2)
		errmessage(8);
	if (argc > 2)
		errmessage(9);
	s = ".cub";
	i = ft_strlen(file);
	if (ft_strncmp(file + (i - 4), s, 4) != 0)
		errmessage(5);
}

int	ft_create_file(char **argv, t_data *data)
{
	int	fd;
	int	i;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_free(data);
		close(fd);
		return (1);
	}
	data->map = ft_calloc(data->map_size + 1, sizeof(*data->map));
	if (!data->map)
		return (free(data->map), 1);
	i = 0;
	while (fd > 0)
	{
		data->map[i] = get_next_line(fd);
		if (data->map[i] == NULL)
			break ;
		i++;
	}
	if (data->map_size != i)
	{
		close(fd);
		ft_free(data);
		return (1);
	}
	if (fd == -1)
	{
		close(fd);
		ft_free(data);
		return (1);
	}
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
	{
		close(fd);
		exit(0);
	}
	while (fd > 0)
	{
		rd = get_next_line(fd);
		if (rd == NULL)
			break ;
		i++;
		free(rd);
	}
	close(fd);
	data->map_size = i;
	if (ft_create_file(argv, data))
		return (1);
	// ft_print_map(data->map);
	valid(data->map, data);
	printf("NO:%s", data->no);
	printf("SO:%s", data->so);
	printf("WE:%s", data->we);
	printf("EA%s", data->ea);
	ft_free(data);
	return (0);
}

int	extract_path(char *file, int j, t_data *data)
{
	int i;
	int l;

	i = 0;
	l = j - 2;
	while (file[j])
	{
		if (file[j] == '.')
		{
			while (file[j] && (file[j] != ' ' && file[j] != '	'))
			{
				i++;
				j++;
			}
			break;
		}
		j++;
	}
	// printf("l: %c\n", file[l]);
	if (file[l] == 'N')
		data->no = ft_substr(file, j - i, i);
	if (file[l] == 'S')
		data->so = ft_substr(file, j - i, i);
	if (file[l] == 'W')
		data->we = ft_substr(file, j - i, i);
	if (file[l] == 'E')
		data->ea = ft_substr(file, j - i, i);
	// printf("%s\n", data->no);
	return (j);
}

int	check_info(char *file, int j, t_data *data)
{
	if (file[j] == 'N' && file[j + 1] == 'O')
		j = extract_path(file, j + 2, data);
	else if (file[j] == 'S' && file[j + 1] == 'O')
		j = extract_path(file, j + 2, data);
	else if (file[j] == 'W' && file[j + 1] == 'E')
		j = extract_path(file, j + 2, data);
	else if (file[j] == 'E' && file[j + 1] == 'A')
		j = extract_path(file, j + 2, data);
	return (j);
}

int valid(char **file, t_data *data)
{
	int i;
	int j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] != ' ' && file[i][j] != '	')
			{
				j = check_info(file[i], j, data);
			}
			j++;
		}
		i++;
	}
	return (1);
}