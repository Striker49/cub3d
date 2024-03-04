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

// void	insert_path(char *file, int j, int i, t_data *data)
// {

// }

int	extract_color(char *file, int j, t_data *data)
{
	int i;
	int l;

	l = j - 2;
	i = 0;
	while (file[j])
	{
		if (!ft_isalpha(file[j]))
		{
			while (file[j])
			{
				i++;
				j++;
			}
			break;
		}
		j++;
	}
	if (file[l] == 'F')
		data->floor = ft_strtrim(ft_substr(file, j - i, i), "	 "); //trims spaces and tabs
	if (file[l] == 'C')
		data->ceiling = ft_strtrim(ft_substr(file, j - i, i), "	 "); //trims spaces and tabs
	return (i);
}

int	extract_path(char *file, int j, t_data *data)
{
	int i;
	int l;

	i = 0;
	l = j - 2;
	if (file[l] == 'F' || file[l] == 'C')
		i = extract_color(file, j, data);
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
	return (j + i);
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

	while (data->file[i][0] == '\n')
		i++;
	while (data->file[i])
	{
		j = 0;
		data->map[i2] = ft_calloc(ft_strlen(data->file[i]) + 1, sizeof(char));
		while (data->file[i][j])
		{
			// printf("data->map: %c\n", data->file[i][j]);
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
			if (file[i][j] != ' ' && file[i][j] != '	')
			{
				j = check_info(file[i], j, data);
			}
			j++;
		}
		i++;
		if (!paths_colors(data))
			break;
	}
	extract_map(data, i, j);
	return (0);
}