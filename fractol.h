/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include "libft.h"
# include "math.h"
# include <math.h>
# define MBROT 1
# define JULIA 2
# define OTHER 3

typedef struct	s_fdata
{
	void		*mlx;
	void		*win;
	int			win_x;
	int			win_y;
	void		*img;
	char		*str;
	int			b;
	int			size;
	int			end;
	double		mov_x;
	double		mov_y;
	double		zoom;
	double		zoomx;
	double		zoomy;
	int			fractal;

	double		cre;
	double		cim;
	int			max_iterations;
	int			need_transform;
}				t_fdata;

typedef struct	s_comp
{
	int			x;
	int			y;
}				t_comp;

typedef struct	s_rgb
{
	double r;
	double g;
	double b;
}				t_rgb;

typedef struct	s_hsv{
	double h;
	double s;
	double v;
}				t_hsv;

int				close_window(t_fdata *data);
void			redraw(t_fdata *data);
void			reset(t_fdata *data);
t_rgb			hsv2rgb(t_hsv in);
void			img_pixel_put(t_fdata *data, int x, int y, t_rgb color);
int				keycode_handler_1(int keycode, t_fdata *data);
int				keycode_handler_2(int keycode, t_fdata *data);
int				keycode_handler_3(int keycode, t_fdata *data);
void			mbrot(t_fdata *d);
void			julia(t_fdata *data);
void			burning_ship(t_fdata *data);
void			init_mbrot(t_fdata *data);
void			init_julia(t_fdata *data);
void			init_burning_ship(t_fdata *data);
int				mouse_wheel_handler(int key, int x, int y, t_fdata *data);
int				mouse_handler(int x, int y, t_fdata *data);

#endif
