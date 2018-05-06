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

void			init_burning_ship(t_fdata* data)
{
    data->fractal = OTHER;
    data->moveX = -0.5;
    data->moveY = -0.3;
    data->zoom = 1;
    data->zoomX = 400;
    data->zoomY = 320;
    data->maxIterations = 300;
}

static double	ft_abss(double x)
{
	if (x < 0)
		return -x;
	return x;
}

static int      norme_helper_func(t_fdata* data, int* ivar, t_rgb* rgbcolor)
{
    double      dvar[5];

    dvar[0]  = 1.5 * (ivar[0] - data->win_x / 2) / (0.5 * data->zoom * data->win_x) + data->moveX;
    dvar[1] = (ivar[1] - data->win_y / 2) / (0.5 * data->zoom * data->win_y) + data->moveY;
    dvar[2] = dvar[0];
    dvar[3] = dvar[1];
    ivar[2] = 0;
    while (dvar[2] * dvar[2] + dvar[3] * dvar[3] < 4  &&  ivar[2] < data->maxIterations)
    {
        dvar[4] = dvar[2] * dvar[2] - dvar[3] * dvar[3] + dvar[0];
        dvar[3] = ft_abss(2 * dvar[2] * dvar[3] + dvar[1]);
        dvar[2] = ft_abss(dvar[4]);

        ivar[2] = ivar[2] + 1;
    }
    if (ivar[2] == data->maxIterations)
    {
        rgbcolor->r = 0;
        rgbcolor->g = 0;
        rgbcolor->b = 0;
        img_pixel_put(data, ivar[0], ivar[1], *rgbcolor);
        ivar[1]++;
        return 1;
    }
    return 0;
}

void			burning_ship(t_fdata* data)
{
	t_hsv		hsvcolor;
    t_rgb		rgbcolor;
    int         ivar[3];

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
            hsvcolor.v = ivar[2] % 255 * (ivar[2] < data->maxIterations);
            rgbcolor = hsv2rgb(hsvcolor);
            img_pixel_put(data, ivar[0], ivar[1], rgbcolor);
            ivar[1]++;
        }
        ivar[0]++;
	}
}
