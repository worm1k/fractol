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

int 		main()
{
	t_fdata	*data;

	data = (t_fdata *)malloc(sizeof(t_fdata));
	data->argc_2 = 0;

     data->win_x = 800;
     data->win_y = 640;
     data->mlx = mlx_init();
     data->win = mlx_new_window(data->mlx, 800, 640, "fractol");
     data->img = mlx_new_image(data->mlx, 800, 640);
     data->str = mlx_get_data_addr(data->img, &data->b, &data->size, &data->end);
     int i = -5;
     while (i < 5)
     {
         int j = -5;
         while (j < 5)
         {
             img_pixel_put(data, i, j, 0x00ffffff);
             j++;
         }
         i++;
     }
     mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
     mlx_hook(data->win, 2, 5, keycode_handler, data);
     mlx_loop(data->mlx);
	return (0);
}
