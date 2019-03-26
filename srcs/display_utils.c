/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/26 05:33:14 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:02:15 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	check_corner(int i, int j, t_data *data, t_point point)
{
	if (j == 0 && i == 0)
		data->corner.a = point;
	else if (i == 0 && j == data->line_size - 1)
		data->corner.b = point;
	else if (i == data->line_nbr - 1 && j == data->line_size - 1)
		data->corner.c = point;
	else if (i == data->line_nbr - 1 && j == 0)
		data->corner.d = point;
}

t_pix	get_min_max_range(t_pix a, t_pix b, t_pix c, t_pix *max)
{
	t_pix	min;

	min.x = a.x;
	max->x = a.x;
	min.y = a.y;
	max->y = a.y;
	if (b.x > max->x)
		max->x = b.x;
	if (c.x > max->x)
		max->x = c.x;
	if (b.x < min.x)
		min.x = b.x;
	if (c.x < min.x)
		min.x = c.x;
	if (b.y > max->y)
		max->y = b.y;
	if (c.y > max->y)
		max->y = c.y;
	if (b.y < min.y)
		min.y = b.y;
	if (c.y < min.y)
		min.y = c.y;
	return (min);
}

t_hide	new_cpt(int i, int i_end, int j, int j_end)
{
	t_hide	cpt;

	cpt.i = i;
	cpt.i_start = i;
	cpt.i_end = i_end;
	cpt.i_way = i_end - i > 0 ? 1 : -1;
	cpt.j = j;
	cpt.j_end = j_end;
	cpt.j_start = j;
	cpt.j_way = j_end - j > 0 ? 1 : -1;
	return (cpt);
}

t_hide	define_way(t_data *data)
{
	double	test[4];
	t_hide	cpt;
	int		order;

	test[0] = get_magnitude(sub_points(data->cam.from, data->corner.a));
	test[1] = get_magnitude(sub_points(data->cam.from, data->corner.b));
	test[2] = get_magnitude(sub_points(data->cam.from, data->corner.c));
	test[3] = get_magnitude(sub_points(data->cam.from, data->corner.d));
	if (test[0] <= test[1] && test[0] <= test[2] && test[0] <= test[3]
		&& (order = test[1] <= test[3] ? 1 : 2))
		cpt = new_cpt(0, data->line_nbr - 1, 0, data->line_size - 1);
	else if (test[1] <= test[0] && test[1] <= test[2] && test[1] <= test[3]
		&& (order = test[0] <= test[2] ? 1 : 2))
		cpt = new_cpt(0, data->line_nbr - 1, data->line_size - 1, 0);
	else if (test[2] <= test[0] && test[2] <= test[1] && test[2] <= test[3]
		&& (order = test[3] <= test[1] ? 1 : 2))
		cpt = new_cpt(data->line_nbr - 1, 0, data->line_size - 1, 0);
	else if ((order = test[2] <= test[0] ? 1 : 2))
		cpt = new_cpt(data->line_nbr - 1, 0, 0, data->line_size - 1);
	cpt.order = order;
	data->cpt = cpt;
	return (cpt);
}

int		is_in_fov(t_pix a, t_pix b)
{
	if ((a.x < 0 || a.x > WIN_WIDTH || a.y < 0 || a.y > WIN_HEIGHT)
			&& (b.x < 0 || b.x > WIN_WIDTH || b.y < 0 || b.y > WIN_HEIGHT))
		return (0);
	return (1);
}
