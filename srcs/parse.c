/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/04 08:45:45 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:03:41 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_pix	**create_pix_map(int l_size, int l_nbr)
{
	t_pix	**vert_map;
	int		i;

	i = 0;
	if (!(vert_map = (t_pix **)malloc(sizeof(t_pix *) * l_nbr)))
		return (NULL);
	while (i < l_nbr)
	{
		if (!(vert_map[i] = (t_pix *)malloc(sizeof(t_pix) * l_size)))
			return (NULL);
		i++;
	}
	return (vert_map);
}

t_point	set_new_point(double x, double y, double z)
{
	t_point	pt;

	pt.x = x;
	pt.y = y;
	pt.z = z;
	return (pt);
}

int		get_clr(char *clr)
{
	int	color;

	color = 0;
	while (*clr)
	{
		color = (color << 4);
		color += *clr > '9' ? (*clr - 'A' + 10) : (*clr - '0');
		clr++;
	}
	return (((color >> 16) | ((color << 16) & 0xFF0000) | (color & 0xFF00)));
}

int		check_rgb(char *clr)
{
	int	nb;

	nb = 0;
	while (*clr)
	{
		if (!ft_isdigit(*clr) && (*clr < 'A' || *clr > 'F'))
			return (0);
		nb++;
		clr++;
	}
	return (nb != 6 ? 0 : 1);
}

t_data	*get_data(char *file, int argc, char **argv)
{
	t_data	*data;

	if (!(data = init_data(file)))
		return (NULL);
	init_mlx_and_img(data);
	if (!(data->pix_map = create_pix_map(data->line_size, data->line_nbr)))
		return (NULL);
	data->cam = init_camera();
	data->mats = get_mats(data);
	data->params = init_user_params();
	init_colors(data, argc, argv);
	data->fill = 0;
	data->speed = 0.1;
	data->cam_speed = 1.0;
	data->proj = PERSP;
	return (data);
}
