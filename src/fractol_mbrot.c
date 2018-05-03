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

void        init_mbrot(t_fdata *data)
{
    data->fractal = MBROT;
    data->moveX = 0;
    data->moveY = 0;
    data->zoom = 1;
    data->zoomX = 400;
    data->zoomY = 320;
    data->maxIterations = 300;
}

void		mbrot(t_fdata *data)
{
	double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
	t_hsv hsvcolor;
    t_rgb rgbcolor;

	for(int y = 0; y < data->win_y; y += 1)
	{
		for(int x = 0; x < data->win_x; x += 1)
		{
			//calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
            data->cRe = 1.5 * (x - data->win_x / 2) / (0.5 * data->zoom * data->win_x) + data->moveX;
            data->cIm = (y - data->win_y / 2) / (0.5 * data->zoom * data->win_y) + data->moveY;
			newRe = newIm = oldRe = oldIm = 0; //these should start at 0,0
			//"i" will represent the number of iterations
			int i;
			//start the iteration process
            for(i = 0; i < data->maxIterations; i++)
			{
				//remember value of previous iteration
				oldRe = newRe;
				oldIm = newIm;
				//the actual iteration, the real and imaginary part are calculated
                newRe = oldRe * oldRe - oldIm * oldIm + data->cRe;
                newIm = 2 * oldRe * oldIm + data->cIm;
				//if the point is outside the circle with radius 2: stop
				if((newRe * newRe + newIm * newIm) > 4) break;
			}
			//use color model conversion to get rainbow palette, make brightness black if maxIterations reached
			hsvcolor.h = i % 256;
			hsvcolor.s = 255;
            hsvcolor.v = 255 * (i < data->maxIterations);
			rgbcolor = hsv2rgb(hsvcolor);
			//draw the pixel
			img_pixel_put(data, x, y, rgbcolor);
		}
	}
}
