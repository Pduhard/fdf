/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 22:28:19 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 03:22:55 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	free_matrix(double ***mat)
{
	int	i;

	i = 0;
	while (i < 4)
		free((*mat)[i++]);
	free(*mat);
	*mat = NULL;
}

int		free_all(int ret, t_data *data)
{
	int i;
	int	j;

	i = -1;
	if (data)
	{
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.cmd_ptr);
		free_matrix(&data->cam.tt);
		free_matrix(&data->cam.tr);
		free_matrix(&data->mats.proj_mat);
		free_matrix(&data->mats.world_mat);
		free_matrix(&data->mats.rot_x);
		free_matrix(&data->mats.rot_z);
		while (data->map[++i] && (j = -1))
		{
			free(data->pix_map[i]);
			free(data->map[i]);
		}
		free(data->map);
		free(data->pix_map);
		free(data);
	}
	exit(EXIT_SUCCESS);
	return (ret);
}

int		return_and_free(int ret, char ***splited, int ***map, char **line)
{
	int		i;

	i = 0;
	if (*splited)
	{
		while ((*splited)[i])
			ft_strdel(&(*splited)[i++]);
		free(*splited);
	}
	if (*map)
	{
		i = 0;
		if (ret == 0)
			while ((*map)[i])
				free((*map)[i++]);
		free(*map);
	}
	*map = NULL;
	ft_strdel(line);
	return (ret);
}
