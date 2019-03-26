/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/04 15:29:28 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:02:50 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		put_pixel_to_image(t_pix pix, char *img_str)
{
	int		pos;

	pos = (round(pix.y) * WIN_WIDTH + round(pix.x)) * 4;
	if (img_str[pos] + img_str[pos + 1] + img_str[pos + 2] == 0)
	{
		img_str[pos] = pix.r;
		img_str[pos + 1] = pix.g;
		img_str[pos + 2] = pix.b;
	}
}

void		new_pix(t_pix *pos, t_pix a, int i, t_pix step)
{
	pos->x = a.x + i * step.x;
	pos->y = a.y + i * step.y;
	pos->z = a.z + i * step.z;
}

t_pix		div_step_x(t_pix step, int cas)
{
	if (cas == 1)
	{
		step.y /= ft_abs(step.x);
		step.z /= ft_abs(step.x);
		step.x /= ft_abs(step.x);
		return (step);
	}
	step.x /= ft_abs(step.y);
	step.z /= ft_abs(step.y);
	step.y /= ft_abs(step.y);
	return (step);
}

void		draw_line(t_pix a, t_pix b, t_data *data)
{
	t_pix		step;
	int			n;
	int			i;
	t_pix		pos;

	i = 0;
	step.x = b.x - a.x;
	step.y = b.y - a.y;
	step.z = b.z - a.z;
	if (ft_abs(step.x) > ft_abs(step.y) && (n = ft_abs(step.x)))
		step = div_step_x(step, 1);
	else if ((n = ft_abs(step.y)))
		step = div_step_x(step, 2);
	if (n < WIN_WIDTH * 3 / 2)
		while (i < n)
		{
			new_pix(&pos, a, i, step);
			create_color(&pos, round(pos.z), data);
			if ((pos.x >= 0 && pos.x < WIN_WIDTH - 1)
				&& (pos.y >= 0 && pos.y < WIN_HEIGHT - 1))
				put_pixel_to_image(pos, data->mlx.img_str);
			i++;
		}
}
