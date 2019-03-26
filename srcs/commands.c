/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   commands.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/26 04:47:58 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:01:58 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	write_commands_label(int y, char *axe, int cases, t_data *data)
{
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, 1050, y,
		WHITE, (cases & 1) ? "CAMERA" : "OBJECT");
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, 1120, y, WHITE, axe);
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, 1140, y,
		WHITE, (cases & 2) ? "POSITION" : "ROTATION");
}

void	write_commands(int y, char *plus, char *minus, t_data *data)
{
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, 1280, y, WHITE, "+");
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, 1300, y, WHITE, "=");
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, 1320, y, WHITE, plus);
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, 1390, y, WHITE, "-");
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, 1410, y, WHITE, "=");
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, 1430, y, WHITE, minus);
}

void	display_options(t_data *data)
{
	mlx_string_put(data->mlx.mlx_ptr,
		data->mlx.win_ptr, 1050, 940, WHITE, "FILL =");
	mlx_string_put(data->mlx.mlx_ptr,
		data->mlx.win_ptr, 1130, 940, WHITE, "space");
	mlx_string_put(data->mlx.mlx_ptr,
		data->mlx.win_ptr, 1260, 940, WHITE, "CHANGE");
	mlx_string_put(data->mlx.mlx_ptr,
		data->mlx.win_ptr, 1330, 940, WHITE, "PERSPECTIVE =");
	mlx_string_put(data->mlx.mlx_ptr,
		data->mlx.win_ptr, 1480, 940, WHITE, "p");
}

void	display_commands(t_data *data)
{
	write_commands_label(70, "Z", 3, data);
	write_commands(70, "S", "W", data);
	write_commands_label(180, "X", 3, data);
	write_commands(180, "D", "A", data);
	write_commands_label(290, "Y", 3, data);
	write_commands(290, "E", "Q", data);
	write_commands_label(400, "X", 1, data);
	write_commands(400, "0", "Lshift", data);
	write_commands_label(510, "X", 0, data);
	write_commands(510, "Uarr", "Darr", data);
	write_commands_label(620, "Z", 0, data);
	write_commands(620, "Rarr", "Larr", data);
	mlx_string_put(data->mlx.mlx_ptr,
		data->mlx.win_ptr, 1050, 730, WHITE, "ROTATION");
	mlx_string_put(data->mlx.mlx_ptr,
		data->mlx.win_ptr, 1140, 730, WHITE, "SPEED");
	write_commands(730, "+", "-", data);
	mlx_string_put(data->mlx.mlx_ptr,
		data->mlx.win_ptr, 1050, 840, WHITE, "MOVEMENT");
	mlx_string_put(data->mlx.mlx_ptr,
		data->mlx.win_ptr, 1140, 840, WHITE, "SPEED");
	write_commands(840, "pageUp", "pageDown", data);
	display_options(data);
}
