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
	data->file_size = i;
	if (ft_create_file(argv, data))
		return (1);

	valid(data->file, data);
	printf("NO:%s", data->no);
	printf("SO:%s", data->so);
	printf("WE:%s", data->we);
	printf("EA:%s", data->ea);
	printf("F:%s", data->floor);
	printf("C:%s", data->ceiling);
	printf("MAP:\n");
	ft_print_map(data->map);
	ft_free(data);
	return (0);
}

char	*insert_path(char *direction, char *path, char *path_name)
{
	if (direction != NULL)
	{
		errmessage(2, path_name);
	}
	else
		direction = ft_strdup(path);
	// free(path);
	return (direction);
}

int	extract_color(char *file, int j, t_data *data)
{
	int i;
	int l;
	char *path;

	l = j - 2;
	i = 0;
	path = NULL;
	while (file[j])
	{
		if (!ft_isalpha(file[j]))
		{
			while (file[j] && (!ft_isalpha(file[j]) || file[j] == ','))
			{
				i++;
				j++;
			}
			break;
		}
		j++;
	}
	if (!ft_isalpha(file[l]))
		errmessage(7, ft_substr(file, j - 2, 1));
	path = ft_substr(file, j - i, i);
	if (file[l] == 'F')
		data->floor = insert_path(data->floor, path, "FLOOR");
	else if (file[l] == 'C')
		data->ceiling = insert_path(data->ceiling, path, "CEILING");
	if (path != NULL)
		free(path);
	return (j);
}

int	extract_path(char *file, int j, t_data *data)
{
	int i;
	int l;
	char *path;

	i = 0;
	l = j - 2;
	path = NULL;
	if (file[l] == 'F' || file[l] == 'C')
		j = extract_color(file, j, data);
	else
	{
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
		path = ft_substr(file, j - i, i);
		if (file[l] == 'N')
			data->no = insert_path(data->no, path, "NORTH");
		else if (file[l] == 'S')
			data->so = insert_path(data->so, path, "SOUTH");
		else if (file[l] == 'W')
			data->we = insert_path(data->we, path, "WEST");
		else if (file[l] == 'E')
			data->ea = insert_path(data->ea, path, "EAST");
		if (path != NULL)
			free(path);
	}
	return (j - 1);
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
	else if (file[j] == 'F')
		j = extract_path(file, j + 2, data);
	else if (file[j] == 'C')
		j = extract_path(file, j + 2, data);
	else if (ft_isdigit(file[j]))
		errmessage(4, NULL);
	else if (file[j] != ' ' && file[j] != '	' && file[j] != 0)
		errmessage(7, ft_substr(file, j, 1));
	return (j);
}

int paths_colors(t_data *data)
{
	if (!data->no || !data->so || !data->ea || !data->we || !data->floor || !data->ceiling)
		return (1);
	return (0);
}

void	extract_map(t_data *data, int i, int j)
{
	int i2;

	i2 = 0;
	data->map = ft_calloc(data->file_size + 1, sizeof(*data->map));
	if (!data->map)
		printf("bongo dingo\n");
	while (data->file[i] && !ft_isdigit(data->file[i][j]))
	{
		while (data->file[i][j] && ft_iswhitesp(data->file[i][j]))
			j++;
		if (ft_isalpha(data->file[i][j]))
			errmessage(7, ft_substr(data->file[i], j, 1));
		j = 0;
		i++;
	}
	while (data->file[i])
	{
		j = 0;
		data->map[i2] = ft_calloc(ft_strlen(data->file[i]) + 1, sizeof(char));
		while (data->file[i][j])
		{
			data->map[i2][j] = data->file[i][j];
			j++;
		}
		i++;
		i2++;
	}
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
			if (file[i][j] != ' ' && file[i][j] != '	' && file[i][j] != '\n' && file[i][j] != 0)
				j = check_info(file[i], j, data);
			j++;
		}
		i++;
		if (!paths_colors(data))
			break;
	}
	extract_map(data, i, j);
	if (data->map[0] == NULL)
		errmessage(10, NULL);
	return (0);
}