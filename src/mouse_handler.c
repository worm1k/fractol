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

static int	mouse_key_handler(int key, int x, int y, t_fdata *data)
{
	printf("KEY:%d X:%d Y:[%d]\n", key, x, y);
}

int 		mouse_handler(int x, int y, t_fdata *data)
{
	if (x < 0 || data->win_x <= x || y < 0 || data->win_y <= y)
		return 0;
	printf("X:%d Y:[%d]\n", x, y);
	mlx_mouse_hook(data->win, mouse_key_handler, data);
	return 0;
}

