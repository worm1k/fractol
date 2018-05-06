/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 19:44:03 by abykov            #+#    #+#             */
/*   Updated: 2017/01/16 19:44:04 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void        print_usage()
{
    ft_putendl("usage: ./fractol [1|2|3]");
    ft_putendl("1: MBrot");
    ft_putendl("2: Julia");
    ft_putendl("3: Burning Ship");
    exit(0);
}

static void        init_all(t_fdata* data, int option)
{
    if (option < 1 || 3 < option)
        return print_usage();
    data->win_x = 800;
    data->win_y = 640;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, data->win_x, data->win_y, "fractol");
    data->img = mlx_new_image(data->mlx, data->win_x, data->win_y);
    data->str = mlx_get_data_addr(data->img, &data->b, &data->size, &data->end);
    if (option == MBROT)
    {
        init_mbrot(data);
        mbrot(data);
    }
    else if (option == JULIA)
    {
        init_julia(data);
        julia(data);
    }
    else if (option == OTHER)
    {
        init_burning_ship(data);
        burning_ship(data);
    }
}

int 		main(int argc, char** argv)
{
    t_fdata	data;

	if (argc != 2)
        print_usage();
	int option = ft_atoi(argv[1]);
    init_all(&data, option);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_hook(data.win, 2, 5, keycode_handler_1, &data);
    mlx_hook(data.win, 6, 5, mouse_handler, &data);
    mlx_mouse_hook(data.win, mouse_wheel_handler, &data);
    mlx_hook(data.win, 17, 1L << 17, close_window, &data);
    mlx_loop(data.mlx);
	return (0);
}
