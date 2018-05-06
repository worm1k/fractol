/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_handler_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int			keycode_handler_2(int keycode, t_fdata *data)
{
    if (keycode == 123)
		left(data);
    else if (keycode == 124)
		right(data);
    else if (keycode == 125)
		down(data);
    else if (keycode == 126)
        up(data);
	return 0;
}
