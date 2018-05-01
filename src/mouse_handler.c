/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void suppress_warning(int x, int y)
{
	(void)x;
	(void)y;
}

int			mouse_wheel_handler(int key, int x, int y, t_fdata *data)
{
	printf("KEY:%d X:%d Y:[%d]\n", key, x, y);
	suppress_warning(x, y);
	if (key == 5)
	{
		data->zoom /= 1.1;
		data->moveX += -((data->win_x / 2 - data->zoomX)) / 1000 / data->zoom;
		data->moveY += -((data->win_y / 2 - data->zoomY)) / 1000 / data->zoom;
	}
	if (key == 4)
	{
		data->zoom *= 1.1;
		data->moveX += -((data->win_y / 2 - data->zoomX) / 1000) / data->zoom;
		data->moveY += -((data->win_x / 2 - data->zoomY) / 1000) / data->zoom;
	}
	printf("moveX:%f\n", data->moveX);
	printf("moveY:%f\n", data->moveY);
	redraw(data);
	return (0);
}

int 		mouse_handler(int x, int y, t_fdata *data)
{
	if (x < 0 || data->win_x <= x || y < 0 || data->win_y <= y)
		return 0;
	printf("X:%d Y:[%d]\n", x, y);
	data->zoomX = x;
	data->zoomY = y;
	return 0;
}
