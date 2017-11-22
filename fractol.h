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
}					t_fdata;

typedef struct      s_comp
{
    int             x;
    int             y;
}                   t_comp;

int			keycode_handler(int keycode, t_fdata *data);

#endif
