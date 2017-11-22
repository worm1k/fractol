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

typedef struct		s_point
{
	unsigned		color;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned char	alpha;
	float			z;
	float			x;
	float			y;
	float			x0;
	float			y0;
	float			z0;
}					t_point;

typedef struct		s_fdata
{
	t_point			**point;
	void			*mlx;
    void			*win;
	int				win_x;
	int				win_y;
	void			*img;
	char			*str;
	int				b;
	int				size;
	int				end;
	unsigned		default_color;
	int				argc_2;
}					t_fdata;

int			keycode_handler(int keycode, t_fdata *data);

#endif
