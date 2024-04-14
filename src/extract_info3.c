#include "cub3d.h"

char	*trim_spaces(t_data *data, char *s, char k)
{
	int		i;
	int		j;
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
	free(temp);
	return (temp);
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
