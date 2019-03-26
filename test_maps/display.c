/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 15:15:24 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 05:49:01 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	create_color(t_pix *pix, int z, t_data *data)
{
	pix->r = (data->down_clr >> 16) + (z - data->min_z) * data->r_scale;
	pix->g = ((data->down_clr >> 8) & 0xFF) + (z - data->min_z) * data->g_scale;
	pix->b = (data->down_clr & 0xFF) + (z - data->min_z) * data->b_scale;
}

void	display_points(t_pix **pix_map, int **points, t_data *data)
{
	int		i;
	int		j;
	t_point	point;

	i = -1;
	while (++i < data->line_nbr && points && (j = -1))
		while (++j < data->line_size)
		{
			point.x = (double)(j - data->line_size / 2);
			point.y = (double)(i - data->line_nbr / 2);
			point.z = points[i][j];
			pix_map[i][j].z = point.z * data->fun_factor;
			create_color(&pix_map[i][j], point.z, data);
			point = mult_point_matrix(point, data->mats.rot_x);
			point = mult_point_matrix(point, data->mats.rot_z);
			point = mult_point_matrix(point, data->mats.world_mat);
			check_corner(i, j, data, point);
			point = mult_point_matrix(point, data->mats.proj_mat);
			pix_map[i][j].x = round((point.x + 1) * 0.5 * WIN_WIDTH);
			pix_map[i][j].y = round((1 - (point.y + 1) * 0.5) * WIN_HEIGHT);
		}
}

void	link_pix(t_hide *cpt, t_pix **pix_map, t_data *data)
{
	if (((cpt->j < data->line_size - 1 && cpt->j_way > 0)
		|| (cpt->j_way < 0 && cpt->j > 0))
			&& is_in_fov(pix_map[cpt->i][cpt->j],
				pix_map[cpt->i][cpt->j + cpt->j_way]))
		draw_line(pix_map[cpt->i][cpt->j],
			pix_map[cpt->i][cpt->j + cpt->j_way], data);
	if (((cpt->i < data->line_nbr - 1 && cpt->i_way > 0)
		|| (cpt->i > 0 && cpt->i_way < 0))
			&& is_in_fov(pix_map[cpt->i][cpt->j],
				pix_map[cpt->i + cpt->i_way][cpt->j]))
		draw_line(pix_map[cpt->i][cpt->j],
			pix_map[cpt->i + cpt->i_way][cpt->j], data);
	if (cpt->order == 1)
		cpt->j += cpt->j_way;
	else
		cpt->i += cpt->i_way;
}

void	link_pixels(t_pix **pix_map, t_data *data)
{
	t_hide		cpt;

	if (data->line_nbr == 1 && data->line_size == 1)
		put_pixel_to_image(pix_map[0][0], data->mlx.img_str);
	if (data->fill)
		link_fill_pixels(pix_map, data);
	cpt = define_way(data);
	cpt.i_end += cpt.i_end == 0 ? -1 : 1;
	cpt.j_end += cpt.j_end == 0 ? -1 : 1;
	while ((cpt.order == 1 && cpt.i != cpt.i_end)
		|| (cpt.order == 2 && cpt.j != cpt.j_end))
	{
		if (cpt.order == 1)
			cpt.j = cpt.j_start;
		else
			cpt.i = cpt.i_start;
		while ((cpt.order == 2 && cpt.i != cpt.i_end)
			|| (cpt.order == 1 && cpt.j != cpt.j_end))
			link_pix(&cpt, pix_map, data);
		if (cpt.order == 2)
			cpt.j += cpt.j_way;
		else
			cpt.i += cpt.i_way;
	}
}
