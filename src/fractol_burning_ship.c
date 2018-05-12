/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			init_burning_ship(t_fdata *data)
{
	data->fractal = OTHER;
	data->mov_x = -0.5;
	data->mov_y = -0.3;
	data->zoom = 1;
	data->zoomx = 400;
	data->zoomy = 320;
	data->max_iterations = 300;
}

static double	ft_abss(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

static int		norme_helper_func(t_fdata *d, int *i, t_rgb *rgbcolor)
{
	double		v[5];

	v[0] = 1.5 * (i[0] - d->win_x / 2) / (0.5 * d->zoom * d->win_x) + d->mov_x;
	v[1] = (i[1] - d->win_y / 2) / (0.5 * d->zoom * d->win_y) + d->mov_y;
	v[2] = v[0];
	v[3] = v[1];
	i[2] = 0;
	while (v[2] * v[2] + v[3] * v[3] < 4 && i[2] < d->max_iterations)
	{
		v[4] = v[2] * v[2] - v[3] * v[3] + v[0];
		v[3] = ft_abss(2 * v[2] * v[3] + v[1]);
		v[2] = ft_abss(v[4]);
		i[2] = i[2] + 1;
	}
	if (i[2] == d->max_iterations)
	{
		rgbcolor->r = 0;
		rgbcolor->g = 0;
		rgbcolor->b = 0;
		img_pixel_put(d, i[0], i[1], *rgbcolor);
		i[1]++;
		return (1);
	}
	return (0);
}

void			burning_ship(t_fdata *data)
{
	t_hsv		hsvcolor;
	t_rgb		rgbcolor;
	int			ivar[3];

	ivar[0] = 0;
	while (ivar[0] < data->win_x)
	{
		ivar[1] = 0;
		while (ivar[1] < data->win_y)
		{
			if (norme_helper_func(data, ivar, &rgbcolor))
				continue ;
			hsvcolor.h = ivar[2] % 256;
			hsvcolor.s = ivar[2] % 255;
			hsvcolor.v = ivar[2] % 255 * (ivar[2] < data->max_iterations);
			rgbcolor = hsv2rgb(hsvcolor);
			img_pixel_put(data, ivar[0], ivar[1], rgbcolor);
			ivar[1]++;
		}
		ivar[0]++;
	}
}
