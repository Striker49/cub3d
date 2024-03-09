#include "cub3d.h"

char	*insert_path(char *direction, char *path, char *path_name)
{
	if (direction != NULL)
	{
		errmessage(2, path_name);
	}
	else
		direction = ft_strdup(path);
	return (direction);
}

void	find_col_len(char *file, int *i, int *j)
{
	while (file[*j])
	{
		if (ft_isdigit(file[*j]))
		{
			while (file[*j] && (ft_isdigit(file[*j]) \
				|| file[*j] == ',') || file[*j] == ' ' || file[*j] == '	')
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
	char	*temp;
	char	*path;

	l = j - 2;
	i = 0;
	find_col_len(file, &i, &j);
	if (!ft_isalpha(file[l]))
		errmessage(7, ft_substr(file, j - 2, 1));
	temp = ft_substr(file, j - i, i);
	if (ft_strchr(temp, '-'))
		errmessage(11, temp);
	path = ft_strtrim(temp, " 	");
	free(temp);
	if (file[l] == 'F')
		data->floor = insert_path(data->floor, path, "FLOOR");
	else if (file[l] == 'C')
		data->ceiling = \
		insert_path(data->ceiling, path, "CEILING");
	if (!ft_strncmp(path, "", 1))
		errmessage(4, NULL);
	else
		free(path);
	return (j);
}

void	find_path_len(char *file, int *i, int *j)
{
	while (file[*j])
	{
		if (file[*j] == '.')
		{
			while (file[*j] && !ft_iswhitesp(file[*j]) && file[*j] != '\n')
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
		if (!ft_strncmp(path, "", 1))
			errmessage(4, NULL);
		if (path != NULL)
			free(path);
	}
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
	else if (file[j] == 'F')
		j = extract_path(file, j + 2, data);
	else if (file[j] == 'C')
		j = extract_path(file, j + 2, data);
	else if (ft_isdigit(file[j + 2]))
		errmessage(4, ft_substr(file, j, 1));
	else if (file[j] != ' ' && file[j] != '	' && file[j] != 0)
		errmessage(7, ft_substr(file, j, 1));
	if (ft_isalpha(file[j]))
		j = check_info(file, j, data);
	return (j);
}

int	skip_whitesp(int *i, int *j, t_data *data)
{
	while (data->file[*i] && (ft_iswhitesp(data->file[*i][*j]) || data->file[*i][*j] == 0))
	{
		*j = 0;
		while (data->file[*i][*j] && ft_iswhitesp(data->file[*i][*j]))
			(*j)++;
		if (ft_isalpha(data->file[*i][*j]))
			errmessage(7, ft_substr(data->file[*i], *j, 1));
		if (!ft_isdigit(data->file[*i][*j]))
		{
			(*i)++;
			*j = 0;
		}
	}
	if (!ft_isdigit(data->file[*i][*j]) && data->file[*i][*j] != 0)
		errmessage(7, ft_substr(data->file[*i], *j, 1));
	return (0);
}


// char	*lengthen_str(char *line, int diff)
// {
// 	int i;
// 	char *tmp;
// 	int len;

// 	i = 0;
// 	len = ft_strlen(line);
// 	tmp = ft_calloc(sizeof(char), len + diff + 1);
// 	while (tmp[i] != '\n')
// 	{
// 		tmp[i] = line[i];
// 		i++;
// 	}
// 	while (i < (len + diff - 1))
// 	{
// 		tmp[i] = ' ';
// 		i++;
// 	}
// 	tmp[i] = '\n';
// 	printf("lengthen str");
// 	return (tmp);
// }

void	equalize_length(t_data *data, int i, int j)
{
	int		len;
	char	*tmp;
	if (data->map[i] == 0)
		len = 0;
	if (len < data->width)
	{
		while (j < data->width - 1)
		{
			data->map[i][j] = ' ';
			j++;
		}
		data->map[i][j] = '\n';
	}
}

void	extract_map(t_data *data, int i, int j)
{
	int	i2;

	i2 = 0;
	data->map = ft_calloc(data->file_size + 3, sizeof(*data->map));
	if (!data->map)
	{
		ft_free(data);
		printf("bongo dingo\n");
		exit (1);
	}
	if (skip_whitesp(&i, &j, data))
		return ;
	while (data->file[i])
	{
		j = 0;
		data->map[i2] = ft_calloc(data->width + 1, sizeof(char));
		if (i2 == 0 || data->file[i] == NULL)
		{
			equalize_length(data, i2, 0);
			i2++;
		}
		else
		{
			while (data->file[i][j] != '\n' && data->file[i][j] != '\0')
			{
				data->map[i2][j] = data->file[i][j];
				j++;
			}
			equalize_length(data, i2, j);
			i++;
			i2++;
		}
		// data->map[i2] = NULL;
	}
	// equalize_length(data, i2, 0);
}
