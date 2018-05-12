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

static void	suppress_warning(int x, int y)
{
	(void)x;
	(void)y;
}

int			mouse_wheel_handler(int key, int x, int y, t_fdata *data)
{
	suppress_warning(x, y);
	if (key == 5)
	{
		data->zoom /= 1.1;
		data->mov_x += -((data->win_x / 2 - data->zoomx)) / 1000 / data->zoom;
		data->mov_y += -((data->win_y / 2 - data->zoomy)) / 1000 / data->zoom;
	}
	if (key == 4)
	{
		data->zoom *= 1.1;
		data->mov_x += -((data->win_y / 2 - data->zoomx) / 1000) / data->zoom;
		data->mov_y += -((data->win_x / 2 - data->zoomy) / 1000) / data->zoom;
	}
	redraw(data);
	return (0);
}

int			mouse_handler(int x, int y, t_fdata *data)
{
	if (x < 0 || data->win_x <= x || y < 0 || data->win_y <= y)
		return (0);
	if (data->fractal == JULIA && data->need_transform)
	{
		if ((data->win_x / 2) <= x && x < data->win_x)
		{
			data->cim += ((x - data->win_x / 2) * 0.00002);
			data->cre += ((x - data->win_x / 2) * 0.00002);
		}
		if (0 <= x && x < (data->win_x / 2))
		{
			data->cim -= ((data->win_x / 2 - x) * 0.00002);
			data->cre -= ((data->win_x / 2 - x) * 0.00002);
		}
		redraw(data);
	}
	data->zoomx = x;
	data->zoomy = y;
	return (0);
}
