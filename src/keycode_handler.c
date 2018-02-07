/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			redraw(t_fdata *data)
{
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->win_x, data->win_y);
	data->str = mlx_get_data_addr(data->img, &data->b, &data->size, &data->end);
	Julia(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

static void	close_window(t_fdata *data)
{
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
}

static void	left(t_fdata *data)
{
    data->moveX += 0.05;
	redraw(data);
}

static void	right(t_fdata *data)
{
    data->moveX -= 0.05;
	redraw(data);
}

static void	up(t_fdata *data)
{
    data->moveY += 0.05;
	redraw(data);
}

static void	down(t_fdata *data)
{
    data->moveY -= 0.05;
	redraw(data);
}

static void	zoomin(t_fdata *data)
{
    data->zoom += 0.05;
	redraw(data);
}

static void	zoomout(t_fdata *data)
{
    data->zoom -= 0.05;
	redraw(data);
}

int			keycode_handler(int keycode, t_fdata *data)
{
    printf("%d\n", keycode);
    if (keycode == 53) // ESC
        close_window(data);
    if (keycode == 123) // LEFT
        left(data);
    if (keycode == 124) // DOWN
    	right(data);
    if (keycode == 125) // RIGHT
        down(data);
    if (keycode == 126) // UP
        up(data);
    if (keycode == 6) // z
        zoomin(data);
    if (keycode == 7) // x
        zoomout(data);
    return 0;
}
