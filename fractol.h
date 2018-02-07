/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include "libft.h"
# include "math.h"
# include <stdio.h> // delet dis

typedef struct		s_fdata
{
	void			*mlx;
	void			*win;
	int				win_x;
	int				win_y;
	void			*img;
	char			*str;
	int				b;
	int				size;
	int				end;
	double			moveX;
	double			moveY;
	double			zoom;
}					t_fdata;

typedef struct		s_comp
{
	int				x;
	int				y;
}                   t_comp;

typedef struct 		s_rgb
{
	double r;		// a fraction between 0 and 1
	double g;		// a fraction between 0 and 1
	double b;		// a fraction between 0 and 1
} 					t_rgb;

typedef struct		s_hsv{
	double h;       // angle in degrees
	double s;       // a fraction between 0 and 1
	double v;       // a fraction between 0 and 1
}					t_hsv;

t_rgb   		hsv2rgb(t_hsv in);
int				keycode_handler(int keycode, t_fdata *data);
void        	MBrot(t_fdata *data);
void			Julia(t_fdata *data);

#endif
