/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrix.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 13:55:09 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/06 02:47:48 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

double		**get_translation_matrix(t_point vec)
{
	int		i;
	int		j;
	double	**mat;

	if (!(mat = (double **)malloc(sizeof(double *) * 4)))
		return (NULL);
	i = 0;
	while (i < 4)
	{
		if (!(mat[i] = (double *)malloc(sizeof(double) * 4)))
			return (NULL);
		j = -1;
		while (++j < 4)
			mat[i][j] = i == j ? 1 : 0;
		i++;
	}
	mat[3][0] = -vec.x;
	mat[3][1] = -vec.y;
	mat[3][2] = -vec.z;
	return (mat);
}

double		**get_world_matrix(t_point from, t_data *data)
{
	if (data->cam.tt)
		free_matrix(&data->cam.tt);
	if (data->cam.tr)
		free_matrix(&data->cam.tr);
	data->cam.tt = get_translation_matrix(from);
	data->cam.tr = get_rot_x(data->cam.teta);
	return (mat_mult(data->cam.tr, data->cam.tt));
}

double		**get_rot_x(double teta)
{
	double	**mat;
	int		i;
	int		j;

	i = 0;
	if (!(mat = (double **)malloc(sizeof(double *) * 4)))
		return (NULL);
	while (i < 4)
	{
		j = 0;
		if (!(mat[i] = (double *)malloc(sizeof(double) * 4)))
			return (NULL);
		while (j < 4)
			mat[i][j++] = 0;
		i++;
	}
	mat[0][0] = 1;
	mat[1][1] = cos(teta);
	mat[2][1] = -sin(teta);
	mat[1][2] = sin(teta);
	mat[2][2] = cos(teta);
	mat[3][3] = 1;
	return (mat);
}

double		**get_rot_z(double teta)
{
	double	**mat;
	int		i;
	int		j;

	i = 0;
	if (!(mat = (double **)malloc(sizeof(double *) * 4)))
		return (NULL);
	while (i < 4)
	{
		j = 0;
		if (!(mat[i] = (double *)malloc(sizeof(double) * 4)))
			return (NULL);
		while (j < 4)
			mat[i][j++] = 0;
		i++;
	}
	mat[2][2] = 1;
	mat[0][0] = cos(teta);
	mat[0][1] = -sin(teta);
	mat[1][0] = sin(teta);
	mat[1][1] = cos(teta);
	mat[3][3] = 1;
	return (mat);
}

t_matrix	get_mats(t_data *data)
{
	t_matrix	mats;

	mats.proj_mat = get_projection_matrix(data->cam.fov,
		data->cam.near, data->cam.far);
	data->cam.pos = set_new_point(0, 0, data->line_nbr);
	data->cam.from = set_new_point(data->cam.pos.x,
		data->cam.pos.y, data->cam.pos.z);
	mats.world_mat = get_world_matrix(data->cam.from, data);
	mats.teta_x = -2 * M_PI / 4;
	mats.teta_z = 3 * M_PI / 4;
	mats.rot_x = get_rot_x(mats.teta_x);
	mats.rot_z = get_rot_z(mats.teta_z);
	return (mats);
}
