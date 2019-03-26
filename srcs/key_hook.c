/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_hook.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 18:05:54 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:02:43 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		key_press2(int keycode, t_data *data)
{
	if (keycode == 125)
		data->params.m_rotcam_y = 1;
	else if (keycode == 126)
		data->params.p_rotcam_y = 1;
	else if (keycode == 257)
		data->params.m_rotcam_x = 1;
	else if (keycode == 82)
		data->params.p_rotcam_x = 1;
	else if (keycode == 35)
		data->proj = data->proj == PERSP ? ORTO : PERSP;
	else if (keycode == 12)
		data->params.ym_from = 1;
	else if (keycode == 14)
		data->params.yp_from = 1;
	else if (keycode == 3)
		data->params.fun_on = data->params.fun_on ? 0 : 1;
	else if (keycode == 116)
		data->params.p_cam_speed = 1;
	else if (keycode == 121)
		data->params.m_cam_speed = 1;
	else if (keycode == 53)
		return (free_all(1, data));
	return (1);
}

int		key_press(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == 2)
		data->params.xp_from = 1;
	else if (keycode == 0)
		data->params.xm_from = 1;
	else if (keycode == 1)
		data->params.zp_from = 1;
	else if (keycode == 13)
		data->params.zm_from = 1;
	else if (keycode == 124)
		data->params.p_rotcam_z = 1;
	else if (keycode == 123)
		data->params.m_rotcam_z = 1;
	else if (keycode == 49 && data->line_nbr * data->line_size < 25000)
		data->fill = data->fill ? 0 : 1;
	else if (keycode == 69)
		data->params.p_speed = 1;
	else if (keycode == 78)
		data->params.m_speed = 1;
	else
		return (key_press2(keycode, data));
	return (1);
}

int		key_release2(int keycode, t_data *data)
{
	if (keycode == 126)
		data->params.p_rotcam_y = 0;
	else if (keycode == 257)
		data->params.m_rotcam_x = 0;
	else if (keycode == 82)
		data->params.p_rotcam_x = 0;
	else if (keycode == 12)
		data->params.ym_from = 0;
	else if (keycode == 14)
		data->params.yp_from = 0;
	else if (keycode == 116)
		data->params.p_cam_speed = 0;
	else if (keycode == 121)
		data->params.m_cam_speed = 0;
	return (1);
}

int		key_release(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == 2)
		data->params.xp_from = 0;
	else if (keycode == 0)
		data->params.xm_from = 0;
	else if (keycode == 1)
		data->params.zp_from = 0;
	else if (keycode == 13)
		data->params.zm_from = 0;
	else if (keycode == 124)
		data->params.p_rotcam_z = 0;
	else if (keycode == 123)
		data->params.m_rotcam_z = 0;
	else if (keycode == 69)
		data->params.p_speed = 0;
	else if (keycode == 78)
		data->params.m_speed = 0;
	else if (keycode == 125)
		data->params.m_rotcam_y = 0;
	else
		return (key_release2(keycode, data));
	return (1);
}
