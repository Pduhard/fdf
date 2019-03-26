/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   point_op.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/26 02:48:04 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:03:53 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

double	get_magnitude(t_point a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_point	normalize(t_point a)
{
	double		mngt;
	t_point		normalized;

	mngt = get_magnitude(a);
	normalized.x = a.x / mngt;
	normalized.y = a.y / mngt;
	normalized.z = a.z / mngt;
	return (normalized);
}

t_point	cross_product(t_point a, t_point b)
{
	t_point	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

double	dot_product(t_point a, t_point b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_point	sub_points(t_point a, t_point b)
{
	t_point	pt;

	pt.x = a.x - b.x;
	pt.y = a.y - b.y;
	pt.z = a.z - b.z;
	return (pt);
}
