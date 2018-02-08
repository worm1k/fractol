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

void		img_pixel_put(t_fdata *data, int x, int y, t_rgb color)
{
	size_t		i;

	if (x < 0 || y < 0 || data->win_x <= x || data->win_y <= y)
	{
		return ;
	}
	i = y * (data->size) + x * 4;
	data->str[i]     = color.r;
	data->str[i + 1] = color.g;
	data->str[i + 2] = color.b;
}

void            MBrot(t_fdata *data)
{
    double pr, pi;           //real and imaginary part of the pixel p
    double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
    t_hsv hsvcolor;
    t_rgb rgbcolor;
    int maxIterations = 300;//after how much iterations the function should stop

    for(int y = 0; y < data->win_y; y += 1)
    {
        for(int x = 0; x < data->win_x; x += 1)
        {
            //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
            pr = 1.5 * (x - data->win_x / 2) / (0.5 * data->zoom * data->win_x) + data->moveX;
            pi = (y - data->win_y / 2) / (0.5 * data->zoom * data->win_y) + data->moveY;
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

int        ft_exit(t_fdata* data)
{
    exit(0);
    return 0;
}

int 		main(int argc, char** argv)
{
    t_fdata	*data;

    data = (t_fdata *)malloc(sizeof(t_fdata));

    if (argc != 2)
    {
        ft_putendl("usage: ./fractol [1|2|3]");
        ft_putendl("1: MBrot");
        ft_putendl("2: Julia");
        ft_exit(data);
    }
    int option = ft_atoi(argv[1]);
    data->moveX = 0;
    data->moveY = 0;
    data->zoom = 1;
    data->win_x = 800;
    data->win_y = 640;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, data->win_x, data->win_y, "fractol");
    data->img = mlx_new_image(data->mlx, data->win_x, data->win_y);
    data->str = mlx_get_data_addr(data->img, &data->b, &data->size, &data->end);

    if (option == MBROT)
    {
        data->fractal = MBROT;
        MBrot(data);
    }
    else if (option == JULIA)
    {
        data->fractal = JULIA;
        Julia(data);
    }
    else
    {        
        ft_putendl("usage: ./fractol [1|2|3]");
        ft_putendl("1: MBrot");
        ft_putendl("2: Julia");
        exit(0);
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_hook(data->win, 2, 5, keycode_handler, data);
    mlx_hook(data->win, 6, 5, mouse_handler, data);
    mlx_hook(data->win, 17, 1L << 17, ft_exit, &data);
    mlx_loop(data->mlx);
    return (0);
}
