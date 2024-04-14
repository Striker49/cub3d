#include "cub3d.h"

void	ft_reinit_var(t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->c = 0;
	data->temp = ft_calloc(sizeof(int), 2);
	if (!data->temp)
	{
		// free all
		exit(-1);
	}
}

char	*trim_spaces(t_data *data, char *s, char k)
{
	ft_reinit_var(data);
	while (s[data->i])
	{
		if (ft_isdigit(s[data->i]))
			data->temp[data->j++] = s[data->i];
		else if (s[data->i] == ',' || s[data->i] == '\n')
		{
			if (k == 'C')
				data->ceiling[data->c] = ft_atoi(data->temp);
			else
				data->floor[data->c] = ft_atoi(data->temp);
			free(data->temp);
			data->c++;
			data->j = 0;
			data->temp = ft_calloc(sizeof(int), 2);
		}
		data->i++;
	}
	if (k == 'C')
		data->ceiling[data->c] = ft_atoi(data->temp);
	else
		data->floor[data->c] = ft_atoi(data->temp);
	free(data->temp);
	return (data->temp);
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
		data->path[CEILING] = insert_path(data->path[CEILING], path, "CEILING");
	return (j);
}
