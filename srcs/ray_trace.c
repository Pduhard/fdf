/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray_trace.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/26 05:36:21 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:04:10 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ray_triangle_intersect(t_point orig, t_point dir, t_moller *data)
{
	t_point	ab;
	t_point	ac;
	t_point	pvec;
	t_point tvec;
	t_point qvec;

	ab = sub_points(data->b, data->a);
	ac = sub_points(data->c, data->a);
	pvec = cross_product(dir, ac);
	data->det = dot_product(ab, pvec);
	data->inv_det = 1 / data->det;
	tvec = sub_points(orig, data->a);
	data->u = dot_product(tvec, pvec) * data->inv_det;
	if (data->u < -0.0005 || data->u > 1.0005)
		return (0);
	qvec = cross_product(tvec, ab);
	data->v = dot_product(dir, qvec) * data->inv_det;
	if (data->v < -0.0005 || data->u + data->v > 1.0005)
		return (0);
	return (1);
}

void	define_triangle(t_pix c, t_pix **pix_map, t_moller *moller, t_hide cpt)
{
	moller->c = set_new_point(c.x, c.y, 0);
	moller->b = set_new_point(pix_map[cpt.i + cpt.i_way][cpt.j].x,
		pix_map[cpt.i + cpt.i_way][cpt.j].y, 0);
	moller->a = set_new_point(pix_map[cpt.i][cpt.j + cpt.j_way].x,
		pix_map[cpt.i][cpt.j + cpt.j_way].y, 0);
	moller->min = get_min_max_range(c, pix_map[cpt.i][cpt.j + cpt.j_way],
		pix_map[cpt.i + cpt.i_way][cpt.j], &moller->max);
}

void	render_pixel(t_pix c, t_data *data, t_moller moller, t_pix pix)
{
	t_hide cpt;

	cpt = data->cpt;
	pix.r = (moller.v * c.r) + (moller.u * data->pix_map[cpt.i
		+ cpt.i_way][cpt.j].r) + ((1 - moller.u - moller.v)
			* data->pix_map[cpt.i][cpt.j + cpt.j_way].r);
	pix.g = (moller.v * c.g) + (moller.u * data->pix_map[cpt.i
		+ cpt.i_way][cpt.j].g) + ((1 - moller.u - moller.v)
			* data->pix_map[cpt.i][cpt.j + cpt.j_way].g);
	pix.b = (moller.v * c.b) + (moller.u * data->pix_map[cpt.i
		+ cpt.i_way][cpt.j].b) + ((1 - moller.u - moller.v)
			* data->pix_map[cpt.i][cpt.j + cpt.j_way].b);
	put_pixel_to_image(pix, data->mlx.img_str);
}

void	render_triangle(t_pix **pix_map, t_data *data, t_hide cpt, int side)
{
	t_moller	moller;
	t_pix		pix;
	t_point		dir;
	t_point		orig;
	t_pix		c;

	orig = normalize(data->cam.pos);
	c = side == 2 ? pix_map[cpt.i + cpt.i_way][cpt.j + cpt.j_way]
		: pix_map[cpt.i][cpt.j];
	define_triangle(c, pix_map, &moller, cpt);
	pix.y = moller.min.y - 1;
	if ((moller.max.x - moller.min.x) * (moller.max.y - moller.min.y) != 0)
		while (++pix.y <= moller.max.y)
		{
			pix.x = moller.min.x - 1;
			while (++pix.x <= moller.max.x)
				if (pix.x >= 0 && pix.x < WIN_WIDTH - 1
						&& pix.y >= 0 && pix.y < WIN_HEIGHT - 1)
				{
					dir = normalize(set_new_point(pix.x, pix.y, -1));
					if (ray_triangle_intersect(orig, dir, &moller))
						render_pixel(c, data, moller, pix);
				}
		}
}

void	link_fill_pixels(t_pix **pix_map, t_data *data)
{
	t_hide		cpt;

	cpt = define_way(data);
	while ((data->cpt.order == 1 && data->cpt.i != data->cpt.i_end)
		|| (data->cpt.order == 2 && data->cpt.j != data->cpt.j_end))
	{
		if (data->cpt.order == 1)
			data->cpt.j = data->cpt.j_start;
		else
			data->cpt.i = data->cpt.i_start;
		while ((data->cpt.order == 2 && data->cpt.i != data->cpt.i_end)
			|| (data->cpt.order == 1 && data->cpt.j != data->cpt.j_end))
		{
			render_triangle(pix_map, data, data->cpt, 1);
			render_triangle(pix_map, data, data->cpt, 2);
			if (data->cpt.order == 1)
				data->cpt.j += data->cpt.j_way;
			else
				data->cpt.i += data->cpt.i_way;
		}
		if (data->cpt.order == 2)
			data->cpt.j += data->cpt.j_way;
		else
			data->cpt.i += data->cpt.i_way;
	}
}
