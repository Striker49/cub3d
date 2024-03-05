#include "cub3d.h"

char	*insert_path(char *direction, char *path, char *path_name)
{
	if (direction != NULL)
	{
		errmessage(2, path_name);
	}
	else
		direction = ft_strdup(path);
	// if (ft_strncmp(path_name, "FLOOR", 6) \
	// 	|| ft_strncmp(path_name, "CEILING", 8))
	// 	free(path);
	return (direction);
}

void	find_col_len(char *file, int *i, int *j)
{
	while (file[*j])
	{
		if (!ft_isalpha(file[*j]))
		{
			while (file[*j] && (!ft_isalpha(file[*j]) || file[*j] == ','))
			{
				(*i)++;
				(*j)++;
			}
			break ;
		}
		(*j)++;
	}
}

int	extract_color(char *file, int j, t_data *data)
{
	int		i;
	int		l;
	char	*path;

	l = j - 2;
	i = 0;
	path = NULL;
	find_col_len(file, &i, &j);
	if (!ft_isalpha(file[l]))
		errmessage(7, ft_substr(file, j - 2, 1));
	path = ft_substr(file, j - i, i);
	if (file[l] == 'F')
		data->floor = ft_strtrim(insert_path(data->floor, path, "FLOOR"), "	 ");
	else if (file[l] == 'C')
		data->ceiling = \
		ft_strtrim(insert_path(data->ceiling, path, "CEILING"), "	 ");
	if (path != NULL)
		free(path);
	return (j);
}

void	find_path_len(char *file, int *i, int *j)
{
	while (file[*j])
	{
		if (file[*j] == '.')
		{
			while (file[*j] && (file[*j] != ' ' && file[*j] != '	'))
			{
				(*i)++;
				(*j)++;
			}
			break ;
		}
		(*j)++;
	}
}

int	extract_path(char *file, int j, t_data *data)
{
	int		i;
	int		l;
	char	*path;

	i = 0;
	l = j - 2;
	path = NULL;
	if (file[l] == 'F' || file[l] == 'C')
		j = extract_color(file, j, data);
	else
	{
		find_path_len(file, &i, &j);
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
	{
		printf("line: %s\n", file);
		errmessage(7, ft_substr(file, j, 1));
	}
	return (j);
}

void	skip_whitesp(int *i, int *j, t_data *data)
{
	while (data->file[*i] && !ft_isdigit(data->file[*i][*j]))
	{
		while (data->file[*i][*j] && ft_iswhitesp(data->file[*i][*j]))
			(*j)++;
		if (ft_isalpha(data->file[*i][*j]))
			errmessage(7, ft_substr(data->file[*i], *j, 1));
		*j = 0;
		(*i)++;
	}
}

void	extract_map(t_data *data, int i, int j)
{
	int	i2;

	i2 = 0;
	data->map = ft_calloc(data->file_size + 1, sizeof(*data->map));
	if (!data->map)
	{
		ft_free(data);
		printf("bongo dingo\n");
		exit (1);
	}
	skip_whitesp(&i, &j, data);
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
