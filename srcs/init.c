/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/26 04:39:49 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:02:35 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_camera	init_camera(void)
{
	t_camera	cam;

	cam.fov = 90;
	cam.far = 100;
	cam.near = 1;
	cam.teta = 0;
	cam.tt = NULL;
	cam.tr = NULL;
	return (cam);
}

t_param		init_user_params(void)
{
	t_param	param;

	param.xp_from = 0;
	param.xm_from = 0;
	param.yp_from = 0;
	param.ym_from = 0;
	param.zp_from = 0;
	param.zm_from = 0;
	param.p_speed = 0;
	param.m_speed = 0;
	param.p_cam_speed = 0;
	param.m_cam_speed = 0;
	param.p_rotcam_y = 0;
	param.m_rotcam_y = 0;
	param.p_rotcam_z = 0;
	param.m_rotcam_z = 0;
	param.p_rotcam_x = 0;
	param.m_rotcam_x = 0;
	param.fun_on = 0;
	return (param);
}

void		init_mlx_and_img(t_data *data)
{
	int	i;
	int	j;

	data->mlx.mlx_ptr = mlx_init();
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr,
			WIN_WIDTH + 530, WIN_HEIGHT, "fedefe");
	data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT);
	data->mlx.img_str = mlx_get_data_addr(data->mlx.img_ptr,
			&(data->mlx.bpp), &(data->mlx.s_l), &(data->mlx.endian));
	data->mlx.cmd_ptr = mlx_new_image(data->mlx.mlx_ptr, 10, WIN_HEIGHT);
	data->mlx.cmd_str = mlx_get_data_addr(data->mlx.cmd_ptr,
			&(data->mlx.bpp2), &(data->mlx.s_l2), &(data->mlx.endian2));
	i = -1;
	while (++i < WIN_HEIGHT && (j = -1))
		while (++j < 3)
		{
			data->mlx.cmd_str[(i * 10) * 4 + j] = (char)142;
			data->mlx.cmd_str[(i * 10) * 4 + 4 + j] = (char)142;
			data->mlx.cmd_str[(i * 10) * 4 + 8 + j] = (char)142;
			data->mlx.cmd_str[(i * 10) * 4 + 12 + j] = (char)142;
		}
}

t_data		*init_data(char *file)
{
	t_data	*data;
	int		fd;

	data = NULL;
	if ((fd = open(file, O_RDONLY)) <= 0
			|| !(data = (t_data *)malloc(sizeof(t_data))))
	{
		if (fd <= 0)
			ft_printf("Invalid file: \"%s\"\n", file);
		return (NULL);
	}
	data->line_size = -1;
	data->map = NULL;
	data->min_z = 200000000;
	data->max_z = -200000000;
	if (!(data->map = get_map(fd, data)))
	{
		free(data);
		ft_printf("Error on map file\n");
		return (NULL);
	}
	return (data);
}

void		init_colors(t_data *data, int argc, char **argv)
{
	double	clr_div;

	data->down_clr = DFLT_DOWN_CLR;
	data->up_clr = DFLT_UP_CLR;
	if (argc == 4 && !ft_strncmp("--min0x",
				argv[2], 7) && check_rgb(&argv[2][7]))
		data->down_clr = get_clr(&argv[2][7]);
	else
		ft_printf("Default min color choosen\n");
	if (argc == 4 && !ft_strncmp("--max0x",
				argv[3], 7) && check_rgb(&argv[3][7]))
		data->up_clr = get_clr(&argv[3][7]);
	else
		ft_printf("Default max color choosen\n");
	data->fun_factor = 1.0;
	clr_div = (double)(data->max_z - data->min_z);
	if (!clr_div)
		clr_div = 1;
	data->r_scale = (double)((data->up_clr >> 16)
			- (data->down_clr >> 16)) / clr_div;
	data->g_scale = (double)(((data->up_clr >> 8) & 0xFF)
			- ((data->down_clr >> 8) & 0xFF)) / clr_div;
	data->b_scale = (double)((data->up_clr & 0xFF)
			- (data->down_clr & 0xFF)) / clr_div;
}
