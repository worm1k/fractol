/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			init_julia(t_fdata *data)
{
	data->fractal = JULIA;
	data->mov_x = 0;
	data->mov_y = 0;
	data->zoom = 1;
	data->zoomx = 400;
	data->zoomy = 320;
	data->cre = -0.7;
	data->cim = 0.27015;
	data->max_iterations = 300;
	data->need_transform = 1;
}

static void		norme_helper_func(t_fdata *data, double *dvar, int *ivar)
{
	ivar[2] = 0;
	while (ivar[2] < data->max_iterations)
	{
		dvar[2] = dvar[0];
		dvar[3] = dvar[1];
		dvar[0] = dvar[2] * dvar[2] - dvar[3] * dvar[3] + data->cre;
		dvar[1] = 2 * dvar[2] * dvar[3] + data->cim;
		if ((dvar[0] * dvar[0] + dvar[1] * dvar[1]) > 4)
			return ;
		ivar[2]++;
	}
}

void			julia(t_fdata *data)
{
	double		dvar[4];
	int			ivar[3];
	t_hsv		hsvcolor;
	t_rgb		rgbcolor;

	ivar[0] = 0;
	while (ivar[0] < data->win_y)
	{
		ivar[1] = 0;
		while (ivar[1] < data->win_x)
		{
			dvar[0] = 1.5 * (ivar[1] - data->win_x / 2) /
					(0.5 * data->zoom * data->win_x) + data->mov_x;
			dvar[1] = (ivar[0] - data->win_y / 2) /
					(0.5 * data->zoom * data->win_y) + data->mov_y;
			norme_helper_func(data, dvar, ivar);
			hsvcolor.h = ivar[2] % 256;
			hsvcolor.s = ivar[2] % 256;
			hsvcolor.v = ivar[2] % 256 * (ivar[2] < data->max_iterations);
			rgbcolor = hsv2rgb(hsvcolor);
			img_pixel_put(data, ivar[1], ivar[0], rgbcolor);
			ivar[1]++;
		}
		ivar[0]++;
	}
}
