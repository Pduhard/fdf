/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrix_op.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/26 04:08:42 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:03:34 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	transpos_mat(double **mat)
{
	int		i;
	int		j;
	double	tmp;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < i)
		{
			tmp = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j++][i] = tmp;
		}
		i++;
	}
}

double	**mat_mult(double **a, double **b)
{
	int		i;
	int		j;
	int		k;
	double	**mat;

	if (!(mat = (double **)malloc(sizeof(double *) * 4)))
		return (NULL);
	i = 0;
	while (i < 4)
		if (!(mat[i++] = (double *)malloc(sizeof(double) * 4)))
			return (NULL);
	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 4)
		{
			k = -1;
			mat[i][j] = 0;
			while (++k < 4)
				mat[i][j] += a[i][k] * b[k][j];
		}
	return (mat);
}

t_point	mult_point_matrix(t_point point, double **mat)
{
	t_point	new_p;
	double	w;

	new_p.x = point.x * mat[0][0] + point.y
		* mat[1][0] + point.z * mat[2][0] + mat[3][0];
	new_p.y = point.x * mat[0][1] + point.y
		* mat[1][1] + point.z * mat[2][1] + mat[3][1];
	new_p.z = point.x * mat[0][2] + point.y
		* mat[1][2] + point.z * mat[2][2] + mat[3][2];
	w = point.x * mat[0][3] + point.y
		* mat[1][3] + point.z * mat[2][3] + mat[3][3];
	if (w != 1)
	{
		new_p.x /= w;
		new_p.y /= w;
		new_p.z /= w;
	}
	return (new_p);
}
