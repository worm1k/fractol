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

double			ft_abss(double x)
{
	if (x < 0)
		return -x;
	return x;
}

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

void			burning_ship(t_fdata* data)
{
	t_hsv		hsvcolor;
    t_rgb		rgbcolor;

	for (int xx = 0; xx < data->win_x; xx++)
	{
		for (int yy = 0; yy < data->win_y; yy++)
		{
			double x  = 1.5 * (xx - data->win_x / 2) / (0.5 * data->zoom * data->win_x) + data->moveX;
			double y = (yy - data->win_y / 2) / (0.5 * data->zoom * data->win_y) + data->moveY;
			
            double zx = x;
            double zy = y;

            int iteration = 0;
		  
            while (zx * zx + zy * zy < 4  &&  iteration < data->maxIterations)
			{
				double xtemp = zx * zx - zy * zy + x;
                zy = ft_abss(2 * zx * zy + y);
				zx = ft_abss(xtemp);

				iteration = iteration + 1;
			}

            if (iteration == data->maxIterations)
			{
				rgbcolor.r = 0;
				rgbcolor.g = 0;
				rgbcolor.b = 0;
				img_pixel_put(data, xx, yy, rgbcolor);
				continue ;
			}

			hsvcolor.h = iteration % 256;
			hsvcolor.s = iteration % 255;
            hsvcolor.v = iteration % 255 * (iteration < data->maxIterations);
            rgbcolor = hsv2rgb(hsvcolor);
			img_pixel_put(data, xx, yy, rgbcolor);
		}
	}
}
