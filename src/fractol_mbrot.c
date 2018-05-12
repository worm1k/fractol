/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbrot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_mbrot(t_fdata *data)
{
	data->fractal = MBROT;
	data->mov_x = -0.5;
	data->mov_y = 0;
	data->zoom = 1;
	data->zoomx = 400;
	data->zoomy = 320;
	data->max_iterations = 300;
}

static void	norme_helper_func_2(t_fdata *data, int *ivar, double *dvar)
{
	data->cre = 1.5 * (ivar[1] - data->win_x / 2) /
				(0.5 * data->zoom * data->win_x) + data->mov_x;
	data->cim = (ivar[0] - data->win_y / 2) /
				(0.5 * data->zoom * data->win_y) + data->mov_y;
	dvar[0] = 0;
	dvar[1] = 0;
	dvar[2] = 0;
	dvar[3] = 0;
}

static void	norme_helper_func(t_fdata *data, double *dvar, int *ivar)
{
	ivar[2] = 0;
	while (ivar[2] < data->max_iterations)
	{
		dvar[2] = dvar[0];
		dvar[3] = dvar[1];
		dvar[0] = dvar[2] * dvar[2] - dvar[3] * dvar[3] + data->cre;
		dvar[1] = 2 * dvar[2] * dvar[3] + data->cim;
		if ((dvar[0] * dvar[0] + dvar[1] * dvar[1]) > 4)
			break ;
		ivar[2]++;
	}
}

void		mbrot(t_fdata *data)
{
	double	dvar[4];
	int		ivar[3];
	t_hsv	hsvcolor;
	t_rgb	rgbcolor;

	ivar[0] = 0;
	while (ivar[0] < data->win_y)
	{
		ivar[1] = 0;
		while (ivar[1] < data->win_x)
		{
			norme_helper_func_2(data, ivar, dvar);
			norme_helper_func(data, dvar, ivar);
			hsvcolor.h = ivar[2] % 256;
			hsvcolor.s = 255;
			hsvcolor.v = 255 * (ivar[2] < data->max_iterations);
			rgbcolor = hsv2rgb(hsvcolor);
			img_pixel_put(data, ivar[1], ivar[0], rgbcolor);
			ivar[1]++;
		}
		ivar[0]++;
	}
}
