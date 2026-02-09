/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/02/09 19:21:27 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_cam(t_data *d)
{
	t_ipair	i;

	i.y = 0;
	while (i.y < (int)d->cam.img->height)
	{
		i.x = 0;
		while (i.x < (int)d->cam.img->width)
		{
			mlx_put_pixel(d->cam.img, i.x, i.y, color_px(30, 35, 45, 255));
			i.x++;
		}
		i.y++;
	}
}

void	program_loop(void *ptr)
{
	t_data			*d;

	d = (t_data *)ptr;

	print_dbg(d);
	if (throttle_fps() == -1)
		return ;
	key_hooks(d);

	calculate_main_ray(d);
	render_cam(d);
	upd_mmap_data(&d->mmap, d->c, &d->player);
	render_mmap(&d->cam, &d->mmap, &d->c, &d->config.map);
}

int	set_data(t_data *d)
{
	int		ac = 2;
	char	*av[3] = {"bin", "./maps/simple.cub" , NULL};

	if (load_map(ac, av, &d->config) == -1)
		return (-1);
	set_constants(&d->c);
	set_player(&d->config.map, &d->player, d->c, &d->mmap);
	if (set_mlx(d) == -1)
		return (terminate_cub(d, -1), -1);
	return (0);
}

// int	main(int ac, char **av)
int	main(void)
{
	t_data	d = {0};

	d.d_flag = 0;
	if (set_data(&d) == -1)
		return (EXIT_FAILURE);
	mlx_loop_hook(d.mlx, &program_loop, &d);
	mlx_loop(d.mlx);
	return (terminate_cub(&d, 0));
}
