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

void			burning_ship(t_fdata* data)
{
	t_hsv		hsvcolor;
	t_rgb		rgbcolor; //the RGB color value for the pixel

	for (int xx = 0; xx < data->win_x; xx++)
	{
		for (int yy = 0; yy < data->win_y; yy++)
		{
			// double x = scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
			// double y = scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
			// a->real = 1.5 * (x - a->win_x / 2) / (0.5 * a->zoom * a->win_x) + a->move_x_axis;
			// a->imaginary = (y - a->win_y / 2) / (0.5 * a->zoom * a->win_y) + a->move_y_axis;

			double x  = 1.5 * (xx - data->win_x / 2) / (0.5 * data->zoom * data->win_x) + data->moveX;
			double y = (yy - data->win_y / 2) / (0.5 * data->zoom * data->win_y) + data->moveY;
			
			double zx = x; // zx represents the real part of z
			double zy = y; // zy represents the imaginary part of z 

			int iteration = 0;
			int max_iteration = 1000;
		  
			while (zx * zx + zy * zy < 4  &&  iteration < max_iteration) 
			{
				double xtemp = zx * zx - zy * zy + x;
				zy = ft_abss(2 * zx * zy + y); //ft_abss returns the ft_abssolute value
				zx = ft_abss(xtemp);

				iteration = iteration + 1;
			}

			if (iteration == max_iteration) //Belongs to the set
			{
				rgbcolor.r = 0;
				rgbcolor.g = 0;
				rgbcolor.b = 0;
				img_pixel_put(data, xx, yy, rgbcolor);
				continue ;
			}

			hsvcolor.h = iteration % 256;
			hsvcolor.s = iteration % 255;
			hsvcolor.v = iteration % 255 * (iteration < max_iteration);
			rgbcolor = hsv2rgb(hsvcolor);
			//draw the pixel
			img_pixel_put(data, xx, yy, rgbcolor);
		}
	}
}
