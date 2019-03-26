/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/20 06:48:46 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:04:30 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>
# define KEPSILON 0.00000001
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define PERSP 1
# define ORTO 2
# define DFLT_DOWN_CLR (4 << 16) + (47 << 8) + 104
# define DFLT_UP_CLR (251 << 16) + (208 << 8) + 151
# define WHITE (202 << 16) + (202 << 8) + 202
# define USAGE "Usage: ./fdf <source_file>"
# define OPTN "[--min0xBBGGRR --max0xBBGGRR  (optional)]\n"

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
}					t_point;

typedef struct		s_hide
{
	int				i;
	int				i_end;
	int				j;
	int				j_end;
	int				i_way;
	int				j_way;
	int				i_start;
	int				j_start;
	int				order;
}					t_hide;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	void			*cmd_ptr;
	char			*img_str;
	char			*cmd_str;
	int				bpp;
	int				s_l;
	int				endian;
	int				bpp2;
	int				s_l2;
	int				endian2;
}					t_mlx;

typedef struct		s_camera
{
	t_point			pos;
	double			fov;
	double			near;
	double			far;
	double			teta;
	double			**tt;
	double			**tr;
	t_point			from;
	t_point			to;
	t_point			arb;
}					t_camera;

typedef struct		s_matrix
{
	double			**proj_mat;
	double			**world_mat;
	double			**rot_x;
	double			teta_x;
	double			**rot_z;
	double			teta_z;
}					t_matrix;

typedef	struct		s_corner
{
	t_point			a;
	t_point			b;
	t_point			c;
	t_point			d;
}					t_corner;

typedef	struct		s_param
{
	int				xp_from;
	int				xm_from;
	int				yp_from;
	int				ym_from;
	int				zp_from;
	int				zm_from;
	int				p_speed;
	int				m_speed;
	int				p_cam_speed;
	int				m_cam_speed;
	int				p_rotcam_y;
	int				m_rotcam_y;
	int				p_rotcam_z;
	int				m_rotcam_z;
	int				p_rotcam_x;
	int				m_rotcam_x;
	int				fun_on;
}					t_param;

typedef struct		s_pix
{
	double			x;
	double			y;
	double			z;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_pix;

typedef struct		s_moller
{
	t_point			a;
	t_point			b;
	t_point			c;
	double			t;
	double			u;
	double			v;
	double			det;
	double			inv_det;
	t_pix			min;
	t_pix			max;
}					t_moller;

typedef struct		s_data
{
	int				**map;
	t_pix			**pix_map;
	int				line_size;
	int				line_nbr;
	t_matrix		mats;
	t_mlx			mlx;
	t_camera		cam;
	int				fill;
	double			speed;
	double			cam_speed;
	int				proj;
	int				min_z;
	int				max_z;
	int				down_clr;
	int				up_clr;
	double			r_scale;
	double			g_scale;
	double			b_scale;
	double			fun_factor;
	t_param			params;
	t_corner		corner;
	t_hide			cpt;
}					t_data;

t_data				*get_data(char *file, int argc, char **argv);
void				draw_line(t_pix a, t_pix b, t_data *data);
double				**get_projection_matrix(double fov,
						double near, double far);
double				**get_orthographic_matrix(double r,
						double near, double far);
double				**get_world_matrix(t_point from, t_data *data);
t_point				mult_point_matrix(t_point point, double **mat);
void				display_points(t_pix **pix_map, int **points, t_data *data);
void				link_pixels(t_pix **pix_map, t_data *data);
int					key_press(int keycode, void *param);
int					key_release(int keycode, void *param);
t_point				normalize(t_point a);
t_point				set_new_point(double x, double y, double z);
t_point				sub_points(t_point a, t_point b);
t_point				cross_product(t_point a, t_point b);
double				dot_product(t_point a, t_point b);
double				**get_rot_x(double teta);
double				**get_rot_z(double teta);
double				get_magnitude(t_point a);
void				put_pixel_to_image(t_pix pix, char *img_str);
void				create_color(t_pix *pix, int z, t_data *data);
void				display_commands(t_data *data);
t_hide				define_way(t_data *data);
int					print_loop_image(void *param);
void				free_matrix(double ***mat);
int					free_all(int ret, t_data *data);
double				**get_ortho_matrix(t_data *data);
int					return_and_free(int ret,
						char ***splited, int ***map, char **line);
int					**get_map(int fd, t_data *data);
double				**mat_mult(double **a, double **b);
t_matrix			get_mats(t_data *data);
t_camera			init_camera(void);
t_param				init_user_params(void);
void				init_mlx_and_img(t_data *data);
t_data				*init_data(char *file);
void				init_colors(t_data *data, int argc, char **argv);
int					get_clr(char *clr);
int					check_rgb(char *clr);
void				display_commands(t_data *data);
double				check_in_triangle(t_pix a, t_pix b, t_pix pix);
t_pix				get_min_max_range(t_pix a, t_pix b, t_pix c, t_pix *max);
t_hide				define_way(t_data *data);
void				link_fill_pixels(t_pix **pix_map, t_data *data);
void				check_corner(int i, int j, t_data *data, t_point point);
int					is_in_fov(t_pix a, t_pix b);

#endif
