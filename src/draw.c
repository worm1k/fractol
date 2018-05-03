/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
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
    size_t  i;

    if (x < 0 || y < 0 || data->win_x <= x || data->win_y <= y)
    {
        return ;
    }
    i = y * (data->size) + x * 4;
    data->str[i]     = 255 * color.r;
    data->str[i + 1] = 255 * color.g;
    data->str[i + 2] = 255 * color.b;
}

void		redraw(t_fdata *data)
{
    mlx_destroy_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, data->win_x, data->win_y);
    data->str = mlx_get_data_addr(data->img, &data->b, &data->size, &data->end);
    if (data->fractal == JULIA)
        julia(data);
    else if (data->fractal == MBROT)
        mbrot(data);
    else if (data->fractal == OTHER)
        burning_ship(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void        reset(t_fdata *data)
{
    if (data->fractal == JULIA)
        init_julia(data);
    else if (data->fractal == MBROT)
        init_mbrot(data);
    else if (data->fractal == OTHER)
        init_burning_ship(data);
    redraw(data);
}

int     	close_window(t_fdata *data)
{
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
}
