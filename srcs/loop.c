/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/26 02:35:29 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:03:00 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	loop_manage_speed(t_data *data)
{
	if (data->params.p_speed)
		data->speed += 0.01;
	else if (data->params.m_speed)
		data->speed -= 0.01;
	if (data->speed < 0.01)
		data->speed = 0.01;
	if (data->params.p_cam_speed)
		data->cam_speed += 0.1;
	else if (data->params.m_cam_speed)
		data->cam_speed -= 0.1;
	if (data->cam_speed < 0.1)
		data->cam_speed = 0.1;
}

void	loop_manage_render(t_data *data)
{
	if (get_magnitude(sub_points(data->cam.from, set_new_point(0, 0, 0)))
		< (data->line_size + data->line_nbr) / 2)
		data->fill = 0;
	data->fun_factor += data->params.fun_on ? 0.1 : -data->fun_factor + 1.0;
}

void	loop_manage_cam(t_data *data)
{
	if (data->params.xp_from && !data->params.xm_from)
		data->cam.from.x += (data->cam_speed);
	else if (!data->params.xp_from && data->params.xm_from)
		data->cam.from.x -= (data->cam_speed);
	if (data->params.yp_from && !data->params.ym_from)
		data->cam.from.y += (data->cam_speed);
	else if (!data->params.yp_from && data->params.ym_from)
		data->cam.from.y -= (data->cam_speed);
	if (data->params.zp_from && !data->params.zm_from)
		data->cam.from.z += (data->cam_speed);
	else if (!data->params.zp_from && data->params.zm_from)
		data->cam.from.z -= (data->cam_speed);
	if (data->params.p_rotcam_y && !data->params.m_rotcam_y)
		data->cam.teta += data->speed;
	else if (data->params.m_rotcam_y && !data->params.p_rotcam_y)
		data->cam.teta -= data->speed;
}

void	loop_manage_rot_matrix(t_data *data)
{
	if (data->params.p_rotcam_z && !data->params.m_rotcam_z)
		data->mats.teta_z += data->speed;
	else if (data->params.m_rotcam_z && !data->params.p_rotcam_z)
		data->mats.teta_z -= data->speed;
	if (data->params.p_rotcam_x && !data->params.m_rotcam_x)
		data->mats.teta_x += data->speed;
	else if (data->params.m_rotcam_x && !data->params.p_rotcam_x)
		data->mats.teta_x -= data->speed;
	free_matrix(&data->mats.rot_x);
	free_matrix(&data->mats.rot_z);
	free_matrix(&data->mats.world_mat);
	free_matrix(&data->mats.proj_mat);
	data->mats.rot_x = get_rot_x(data->mats.teta_x);
	data->mats.rot_z = get_rot_z(data->mats.teta_z);
	data->mats.world_mat = get_world_matrix(data->cam.from, data);
	if (data->proj == PERSP)
		data->mats.proj_mat = get_projection_matrix(data->cam.fov,
			data->cam.near, data->cam.far);
	else if (data->proj == ORTO)
		data->mats.proj_mat = get_ortho_matrix(data);
}

int		print_loop_image(void *param)
{
	t_data *data;

	data = (t_data *)param;
	loop_manage_speed(data);
	loop_manage_render(data);
	loop_manage_cam(data);
	loop_manage_rot_matrix(data);
	mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
	data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->mlx.img_str = mlx_get_data_addr(data->mlx.img_ptr,
			&(data->mlx.bpp), &(data->mlx.s_l), &(data->mlx.endian));
	display_points(data->pix_map, data->map, data);
	link_pixels(data->pix_map, data);
	mlx_put_image_to_window(data->mlx.mlx_ptr,
		data->mlx.win_ptr, data->mlx.img_ptr, 0, 0);
	return (1);
}
