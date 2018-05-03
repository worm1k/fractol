/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_handler_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void red(t_fdata *data)
{
    data->dr = data->dr + 0.1;
    if (data->dr > 1.0)
        data->dr -= 1.0;
    redraw(data);
}

static void green(t_fdata *data)
{
    data->dg = data->dg + 0.1;
    if (data->dg > 1.0)
        data->dg -= 1.0;
    redraw(data);
}

static void blue(t_fdata *data)
{
    data->db = data->db + 0.1;
    if (data->db > 1.0)
        data->db -= 1.0;
    redraw(data);
}

int			keycode_handler_3(int keycode, t_fdata* data)
{
    //printf("KEY:%d\n", keycode);
    if (keycode == 15)
        red(data);
    else if (keycode == 5)
        green(data);
    else if (keycode == 11)
        blue(data);
    return 0;
}
