/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/04 08:35:11 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 06:49:59 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2 && argc != 4)
		return (ft_printf("%s %s", USAGE, OPTN));
	if (!(data = get_data(argv[1], argc, argv)))
		return (free_all(-1, data));
	display_points(data->pix_map, data->map, data);
	link_pixels(data->pix_map, data);
	display_commands(data);
	mlx_hook(data->mlx.win_ptr, 2, 303, &key_press, (void *)data);
	mlx_hook(data->mlx.win_ptr, 3, 303, &key_release, (void *)data);
	mlx_loop_hook(data->mlx.mlx_ptr, &print_loop_image, (void *)data);
	mlx_put_image_to_window(data->mlx.mlx_ptr,
		data->mlx.win_ptr, data->mlx.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr,
		data->mlx.win_ptr, data->mlx.cmd_ptr, 1000, 0);
	mlx_loop(data->mlx.mlx_ptr);
	return (free_all(0, data));
}
