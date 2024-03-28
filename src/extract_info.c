#include "cub3d.h"

char	*trim_spaces(t_data *data, char *s, char k)
{
	int 	i;
	int 	j;
	int		c;
	char	*temp;

	i = 0;
	j = 0;
	c = 0;
	temp = ft_calloc(sizeof(int), 2);
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			temp[j++] = s[i];
		else if (s[i] == ',' || s[i] == '\n')
		{
			if (k == 'C')
				data->ceiling[c] = ft_atoi(temp);
			else
				data->floor[c] = ft_atoi(temp);	
			free(temp);
			c++;
			j = 0;
			temp = ft_calloc(sizeof(int), 2);
		}
		i++;
	}
	if (k == 'C')
		data->ceiling[c] = ft_atoi(temp);
	else
		data->floor[c] = ft_atoi(temp);	
	return (temp);
}

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
	trim_spaces(data, path, file[l]);
	free(temp);
	if (file[l] == 'F')
		data->path[FLOOR] = insert_path(data->path[FLOOR], path, "FLOOR");
	else if (file[l] == 'C')
		data->path[CEILING] = \
		insert_path(data->path[CEILING], path, "CEILING");
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
