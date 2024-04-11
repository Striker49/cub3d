#include "cub3d.h"

char	*insert_path(char *direction, char *path, char *path_name)
{
	if (direction != NULL)
		errmessage(2, path_name);
	else
		direction = ft_strdup(path);
	if (!ft_strncmp(path, "", 1))
		errmessage(4, NULL);
	if (path != NULL)
		free(path);
	return (direction);
}

void	find_col_len(char *file, int *i, int *j)
{
	while (file[*j])
	{
		if (ft_isdigit(file[*j]))
		{
			while (file[*j] && ((ft_isdigit(file[*j]) || file[*j] == ',') || file[*j] == ' ' || file[*j] == '	'))
			{
				(*i)++;
				(*j)++;
			}
			break ;
		}
		(*j)++;
	}
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
	if (file[l] == 'F' || file[l] == 'C')
		j = extract_color(file, j, data);
	else
	{
		find_path_len(file, &i, &j);
		path = ft_substr(file, j - i, i);
		if (file[l] == 'N')
			data->path[NORTH] = insert_path(data->path[NORTH], path, "NORTH");
		else if (file[l] == 'S')
			data->path[SOUTH] = insert_path(data->path[SOUTH], path, "SOUTH");
		else if (file[l] == 'W')
			data->path[WEST] = insert_path(data->path[WEST], path, "WEST");
		else if (file[l] == 'E')
			data->path[EAST] = insert_path(data->path[EAST], path, "EAST");
	}
	return (j);
}
