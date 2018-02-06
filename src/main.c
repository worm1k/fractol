/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		img_pixel_put(t_fdata *data, int x, int y, rgb color)
{
	size_t		i;

	if (x < 0 || y < 0 || data->win_x - 1 < x || data->win_y - 1 < y)
	{
        ft_putstr("returned\n");
		return ;
	}
	i = y * (data->size) + x * 4;
	data->str[i]     = color.r;
	data->str[i + 1] = color.g;
	data->str[i + 2] = color.b;
}

rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}

t_comp multic(t_comp a, t_comp b)
{
    t_comp res;

    res.x = a.x * b.x - a.y * b.y;
    res.y = a.x * b.y + a.y * b.x;
    return (res);
}

t_comp sumc(t_comp a, t_comp b)
{
    t_comp res;

    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return (res);
}

void            MBrot(t_fdata *data)
{
    double pr, pi;           //real and imaginary part of the pixel p
    double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
    double zoom = 1, moveX = -0.5, moveY = 0; //you can change these to zoom and change position
    hsv hsvcolor;
    rgb rgbcolor;
    int maxIterations = 300;//after how much iterations the function should stop

    t_comp Z;
    t_comp C;
    int iterations;
    for(int y = 0; y <= data->win_y; y += 1)
    {
        for(int x = 0; x <= data->win_x; x += 1)
        {
            //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
            pr = 1.5 * (x - data->win_x / 2) / (0.5 * zoom * data->win_x) + moveX;
            pi = (y - data->win_y / 2) / (0.5 * zoom * data->win_y) + moveY;
            newRe = newIm = oldRe = oldIm = 0; //these should start at 0,0
            //"i" will represent the number of iterations
            int i;
            //start the iteration process
            for(i = 0; i < maxIterations; i++)
            {
                //remember value of previous iteration
                oldRe = newRe;
                oldIm = newIm;
                //the actual iteration, the real and imaginary part are calculated
                newRe = oldRe * oldRe - oldIm * oldIm + pr;
                newIm = 2 * oldRe * oldIm + pi;
                //if the point is outside the circle with radius 2: stop
                if((newRe * newRe + newIm * newIm) > 4) break;
            }
            //use color model conversion to get rainbow palette, make brightness black if maxIterations reached
            hsvcolor.h = i % 256;
            hsvcolor.s = 255;
            hsvcolor.v = 255 * (i < maxIterations);
            rgbcolor = hsv2rgb(hsvcolor);
            //draw the pixel
            img_pixel_put(data, x, y, rgbcolor);
        }
    }
}

int 		main()
{
    t_fdata	*data;

    data = (t_fdata *)malloc(sizeof(t_fdata));

    data->win_x = 800;
    data->win_y = 640;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, 800, 640, "fractol");
    data->img = mlx_new_image(data->mlx, 800, 640);
    data->str = mlx_get_data_addr(data->img, &data->b, &data->size, &data->end);
    int i = -5;
    MBrot(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_hook(data->win, 2, 5, keycode_handler, data);
    mlx_loop(data->mlx);
    return (0);
}
