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

static void		img_pixel_put(t_fdata *data, int x, int y, unsigned color)
{
	size_t		i;

	x += data->win_x / 2.0;
	y += data->win_y / 2.0;
	if (x < 0 || y < 0 || data->win_x - 1 < x || data->win_y - 1 < y)
	{
		return ;
	}
	i = y * (data->size) + x * 4;
	data->str[i] = color % 256;
	data->str[i + 1] = (color / 256) % 256;
	data->str[i + 2] = (color / 256 / 256) % 256;
	data->str[i + 3] = color / 256 / 256 / 256;
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
    float epsilon = 1; // The step size across the X and Y axis
    float x;
    float y;
    int maxIterations = 100; // increasing this will give you a more detailed fractal
    int maxColors = 0x00ffffff; // Change as appropriate for your display.

    t_comp Z;
    t_comp C;
    int iterations;
    for(x = -200; x <= 200; x += epsilon)
    {
        for(y = -200; y <= 200; y += epsilon)
        {
            iterations = 0;
            C.x = x;
            C.y = y;
            Z.x = 0;
            Z.y = 0;
            while(hypot(Z.x, Z.y) < 200 && iterations < maxIterations)
            {
//                Z = Z*Z + C;
                Z = sumc(multic(Z, Z), C);
                iterations++;
            }
            img_pixel_put(data, x, y, 0xffffff % iterations); // depending on the number of iterations, color a pixel.
            ft_putnbr(iterations); ft_putchar('\n');
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
