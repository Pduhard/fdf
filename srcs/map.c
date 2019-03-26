/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/26 04:05:18 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:03:17 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		cpy_map(int **map, int **new_map, int *i, char **splited)
{
	int	j;

	*i = -1;
	if (map)
		while (map[++(*i)])
			new_map[*i] = map[*i];
	else
		*i = 0;
	j = 0;
	while (splited[j])
		j++;
	return (j);
}

int		check_line_size(int i, int j, int **new_map, t_data *data)
{
	if (j != data->line_size || !(new_map[i] = (int *)malloc(sizeof(int) * j)))
	{
		free(new_map);
		return (0);
	}
	return (1);
}

int		add_line(int ***map, char **line, int rsize, t_data *data)
{
	int		**new_map;
	int		i;
	char	**splited;
	int		j;

	splited = NULL;
	if (!(new_map = (int **)malloc(sizeof(int *) * rsize))
		|| !(splited = ft_strsplit(*line, ' ')))
		return (return_and_free(0, &splited, map, line));
	j = cpy_map(*map, new_map, &i, splited);
	data->line_size = data->line_size == -1 ? j : data->line_size;
	if (!check_line_size(i, j, new_map, data) || !(j = -1))
		return (return_and_free(0, &splited, map, line));
	while (splited[++j])
	{
		new_map[i][j] = ft_atoi(splited[j]);
		if (new_map[i][j] < data->min_z)
			data->min_z = new_map[i][j];
		if (new_map[i][j] > data->max_z)
			data->max_z = new_map[i][j];
	}
	new_map[++i] = NULL;
	return_and_free(1, &splited, map, line);
	*map = new_map;
	return (1);
}

int		**get_map(int fd, t_data *data)
{
	int		**map;
	char	*line;
	int		size;

	size = 1;
	line = NULL;
	map = NULL;
	while (get_next_line(fd, &line) > 0 && ++size)
		if (!(add_line(&map, &line, size, data)))
		{
			while (get_next_line(fd, &line))
				ft_strdel(&line);
			return (NULL);
		}
	data->line_nbr = size - 1;
	return (map);
}
