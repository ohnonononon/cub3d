/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/18 17:47:23 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Int.h"
#include <math.h>

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

void	calculate_rays(data_t *data, player_t *pl)
{
	irays_t a;
	frays_t	b;

	b.ra = pl->angle;
	a.r = 0;
	while (a.r < 1)
	{
		a.dof = 0;
		float	aTan=-1/tan(b.ra);
		if(b.ra > PI) // Looking up
		{
			b.r.y = (((int)pl->p.y >> 6) << 6) - 0.0001;
			b.r.x = (pl->p.y - b.r.y) * aTan + pl->p.x;
			b.o.y = -64;
			b.o.x -= -b.o.y * aTan;
		}
		if(b.ra < PI) // Looking down
		{
			b.r.y = (((int)pl->p.y >> 6) << 6) + 64;
			b.r.x = (pl->p.y - b.r.y) * aTan + pl->p.x;
			b.o.y = 64;
			b.o.x -= -b.o.y * aTan;
		}
		if (fabsf(b.ra) < data->c.eps || fabsf(b.ra - (float)PI) < data->c.eps)
		{
			b.r.x = pl->p.x;
			b.r.y = pl->p.y;
			a.dof = 8; // que chucha es dof
		}
		while (a.dof < 8)
		{
			a.m.x = (int) (b.r.x) >> 6;
			a.m.y = (int) (b.r.y) >> 6;
			a.mp = a.m.y * data->mapdata.x + a.m.x;
			if (a.mp > 0 && a.mp < data->mapdata.size && data->mapdata.map[a.mp] == 1)
			{
				a.dof = 8;
			}
			else
			{
				b.r.x += b.o.x;
				b.r.y += b.o.y;
				a.dof += 1;
			}
		}
		a.r++;
	}
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
	calculate_rays(d, &d->player);
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
