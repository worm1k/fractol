/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsv_to_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_rgb    norme_helper_func_2(t_hsv in, double* dvar, long i)
{
    t_rgb       out;

    if (i == 3)
    {
        out.r = dvar[1];
        out.g = dvar[2];
        out.b = in.v;
    }
    else if (i == 4)
    {
        out.r = dvar[3];
        out.g = dvar[1];
        out.b = in.v;
    }
    else
    {
        out.r = in.v;
        out.g = dvar[1];
        out.b = dvar[2];
    }
    return (out);
}

static t_rgb    norme_helper_func(t_hsv in, double* dvar, long i)
{
    t_rgb       out;

    if (i == 0)
    {
        out.r = in.v;
        out.g = dvar[3];
        out.b = dvar[1];
    }
    else if (i == 1)
    {
        out.r = dvar[2];
        out.g = in.v;
        out.b = dvar[1];
    }
    else if (i == 2)
    {
        out.r = dvar[1];
        out.g = in.v;
        out.b = dvar[3];
    }
    else
        return norme_helper_func_2(in, dvar, i);
    return out;
}

t_rgb			hsv2rgb(t_hsv in)
{
    double      dvar[5];
	long		i;
	t_rgb		out;

    if(in.s <= 0.0)
    {
		out.r = in.v;
		out.g = in.v;
		out.b = in.v;
		return out;
	}
    dvar[0] = in.h;
    if(dvar[0] >= 360.0) dvar[0] = 0.0;
    dvar[0] /= 60.0;
    i = (long)dvar[0];
    dvar[4] = dvar[0] - i;
    dvar[1] = in.v * (1.0 - in.s);
    dvar[2] = in.v * (1.0 - (in.s * dvar[4]));
    dvar[3] = in.v * (1.0 - (in.s * (1.0 - dvar[4])));
    return (norme_helper_func(in, dvar, i));
}
