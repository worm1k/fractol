/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_handler_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoomin(t_fdata *data)
{
	data->zoom *= 1.1;
	redraw(data);
}

static void	zoomout(t_fdata *data)
{
	data->zoom /= 1.1;
	redraw(data);
}

static void	iterplus(t_fdata *data)
{
	if (data->max_iterations < 10)
		data->max_iterations += 1;
	else if (data->max_iterations < 291)
		data->max_iterations += 10;
	else
		return ;
	redraw(data);
}

static void	iterminus(t_fdata *data)
{
	if (data->max_iterations > 10)
		data->max_iterations -= 10;
	else if (data->max_iterations > 1)
		data->max_iterations -= 1;
	else
		return ;
	redraw(data);
}

int			keycode_handler_1(int keycode, t_fdata *data)
{
	if (keycode == 53)
		close_window(data);
	else if (keycode == 6)
		zoomin(data);
	else if (keycode == 7)
		zoomout(data);
	else if (keycode == 49)
		data->need_transform = 1 - data->need_transform;
	else if (keycode == 0)
		iterminus(data);
	else if (keycode == 1)
		iterplus(data);
	else if (keycode == 36)
		reset(data);
	else
		keycode_handler_2(keycode, data);
	return (0);
}
