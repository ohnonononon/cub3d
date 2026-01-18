/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/18 16:08:01 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Int.h"

// iterates on the ammount of tiles
void	render_mmap(data_t *d, player_t	*pl)
{
	int32_t		color;
	int			i;

	(void)pl;
	i = 0;
	while (i < d->mapdata.size)
	{
		color = set_color_mmap(d->mapdata.map[i]);
		paint_pixel_mmap(d, i % d->mapdata.x, i / d->mapdata.x, color);
		i++;
	}
	draw_player(&d->mmap, pl->p, d->c.pl_radius, d->c.mmap_scale);
	draw_sensor(&d->mmap, pl->p, d->c.mmap_scale, &d->player.line);
}

void	render_cam(data_t *d)
{
	ipair_t	i;

	i.x = 0;
	i.y = 0;
	while (i.y < (int)d->cam.img->height)
	{
		while (i.x < (int)d->cam.img->width)
		{
			mlx_put_pixel(d->cam.img, i.x, i.y, color_px(30, 35, 45, 255));
			i.x++;
		}
		i.y++;
		i.x = 0;
	}
}

#include <sys/time.h>

static double	get_time_ms(void)
{
    struct timeval	tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

int	throttle_fps()
{
	static double	last_frame = 0;
	double			now;
	double			dt;

	now = get_time_ms();
	dt = now - last_frame;
	if (dt < 1000.0/60.0)
		return (-1);
	last_frame = now;
	return (0);
}

void	program_loop(void *ptr)
{
	data_t			*d;

	d = (data_t *)ptr;

	print_dbg(d);
	if (throttle_fps() == -1)
		return ;
	key_hooks(d);
	render_cam(d);
	render_mmap(d, &d->player);
}

int	main(void)
{
	data_t	d = {0};

	if (set_mapdata(&d.mapdata) == -1)
		return (EXIT_SUCCESS);
	set_constants(&d.c);
	set_player(&d.player, &d.cam, &d.mmap);
	if (set_mlx(&d) == -1)
		return (terminate_cub(&d, -1));
	mlx_loop_hook(d.mlx, &program_loop, &d);
	mlx_loop(d.mlx);
	return (terminate_cub(&d, 0));
}
