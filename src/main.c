/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/19 00:09:59 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Int.h"
#include <math.h>

// iterates on the ammount of tiles

void	calculate_line_mmap(player_t *p, line_t *line, fpair_t start, double scale)
{
	line->start.x = (start.x + p->dp.x * p->rad_size) * scale;
	line->start.y = (start.y + p->dp.y * p->rad_size) * scale;
	line->end.x = (start.x + p->dp.x * 30) * scale;
	line->end.y = (start.y + p->dp.y * 30) * scale;
	line->delta.x = -(line->end.x - line->start.x);
	line->delta.y = -(line->end.y - line->start.y);
	line->draw.steps = util_get_max(line->delta.x, line->delta.y);
	line->draw.thick.x = -p->dp.y;
	line->draw.thick.y = p->dp.x;
	line->draw.color = color_px(209, 107, 165, 255); // coolest color tho
}

void	draw_line_mmap(mlx_image_t *img, fpair_t start, fpair_t delta, draw_t draw)
{
	fpair_t	pos;
	fpair_t	inc;
	int		i;
	int		w;

	w = -2;
	while (++w <= 1)
	{
		pos.x = start.x + draw.thick.x * (float) w;
		pos.y = start.y + draw.thick.y * (float) w;
		inc.x = delta.x / draw.steps;
		inc.y = delta.y / draw.steps;
		i = draw.steps;
		while (i--)
		{
			if (pos.x >= 0&& pos.x < img->width && \
				pos.y >= 0 && pos.y < img->height)
				mlx_put_pixel(img, pos.x, pos.y, draw.color);
			pos.x += inc.x;
			pos.y += inc.y;
		}
	}
}
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
	calculate_line_mmap(pl, &d->line, pl->p, d->c.mmap_scale);
	draw_line_mmap(d->mmap.img, d->line.start, d->line.delta, d->line.draw);
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

	// calculate_rays(d, &d->player);

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
