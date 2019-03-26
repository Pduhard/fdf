/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   projection.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/26 02:51:59 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:04:01 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

double	**get_projection_matrix(double fov, double near, double far)
{
	double	scale;
	double	**mat;
	int		i;
	int		j;

	i = 0;
	scale = 1 / tan(fov * 0.5 * M_PI / 180);
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
	mat[0][0] = scale;
	mat[1][1] = scale;
	mat[2][2] = -1 * far / (far - near);
	mat[3][2] = -1 * far * near / (far - near);
	mat[2][3] = -1;
	return (mat);
}

double	**get_orthographic_matrix(double r, double near, double far)
{
	int		i;
	int		j;
	double	**mat;

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
	mat[0][0] = 2 / (2 * r);
	mat[1][1] = 2 / (2 * r);
	mat[2][2] = -2 / (far - near);
	mat[3][2] = -(far + near) / (far - near);
	mat[3][3] = 1;
	return (mat);
}

double	**get_ortho_matrix(t_data *data)
{
	t_point	min;
	t_point	max;
	t_point	cam_min;
	t_point	cam_max;

	min = set_new_point(0, 0, data->min_z);
	max = set_new_point(data->line_size, data->line_nbr, data->max_z);
	cam_min = mult_point_matrix(min, data->mats.world_mat);
	cam_max = mult_point_matrix(max, data->mats.world_mat);
	if (cam_min.x > cam_max.x)
		cam_max.x = cam_min.x;
	if (cam_min.y > cam_max.y)
		cam_max.y = cam_min.y;
	if (cam_max.y > cam_max.x)
		cam_max.x = cam_max.y;
	return (get_orthographic_matrix(cam_max.x, data->cam.near, data->cam.far));
}
