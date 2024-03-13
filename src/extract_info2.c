#include "cub3d.h"

int	skip_whitesp(int *i, int *j, t_data *data)
{
	if (data->file[*i] == NULL)
		return (1);
	while (data->file[*i] && (ft_iswhitesp(data->file[*i][*j]) \
	|| data->file[*i][*j] == 0))
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
	if (skip_whitesp(&i, &j, data))
		return ;
	while (data->file[i])
	{
		j = 0;
		data->map[i2] = ft_calloc(data->width + 1, sizeof(char));
		while (data->file[i][j] != '\0')
		{
			data->map[i2][j] = data->file[i][j];
			j++;
		}
		i++;
		i2++;
	}
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
