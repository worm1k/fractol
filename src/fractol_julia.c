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

void            init_julia(t_fdata *data)
{
    data->fractal = JULIA;
    data->moveX = 0;
    data->moveY = 0;
    data->zoom = 1;
    data->zoomX = 400;
    data->zoomY = 320;
    data->cRe = -0.7;
    data->cIm = 0.27015;
    data->maxIterations = 300;
    data->need_transform = 1;
}

void			julia(t_fdata *data)
{
	//each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
	double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
	t_hsv hsvcolor;
    t_rgb rgbcolor; //the RGB color value for the pixel

	for(int y = 0; y < data->win_y; y += 1)
	{
		for(int x = 0; x < data->win_x; x += 1)
		{
			//calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
			newRe = 1.5 * (x - data->win_x / 2) / (0.5 * data->zoom * data->win_x) + data->moveX;
			newIm = (y - data->win_y / 2) / (0.5 * data->zoom * data->win_y) + data->moveY;
			//i will represent the number of iterations
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
				if((newRe * newRe + newIm * newIm) > 4) 
					break;
			}
			//use color model conversion to get rainbow palette, make brightness black if maxIterations reached
			hsvcolor.h = i % 256;
			hsvcolor.s = i % 256;
            hsvcolor.v = i % 256 * (i < data->maxIterations);
			rgbcolor = hsv2rgb(hsvcolor);
			//draw the pixel
			img_pixel_put(data, x, y, rgbcolor);
		}
	}
}
