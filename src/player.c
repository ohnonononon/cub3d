/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:43:39 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/18 17:49:19 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"

// TODO:
// Set coordinates in constants based off mapdata
void	set_player(player_t *d, cam_t *cam, mmap_t *mmap)
{
	mmap->player = d;
	(*cam).player = d;
	d->p.x = 75;
	d->p.y = 75;
	d->angle = 2;
	d->dp.x = cosf(d->angle);
	d->dp.y = sinf(d->angle);
}

static void	render_player(mmap_t *mmap, fpair_t p, fpair_t c, double radius)
{
	int32_t	color;
	int		r;

	color = color_px(209, 107, 165, 120);
	r = radius * radius;
	if ((p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y) <= r)
	{
		if (p.x >= 0 && p.x < mmap->img->width && p.y >= 0 && \
			p.y < mmap->img->height)
			mlx_put_pixel(mmap->img, p.x, p.y, color);
	}
}

// Draws player as a circle. var c is the definitive origin point.
// C is position.
// P is total area space
void	draw_player(mmap_t *mmap, fpair_t c, int radius, double scale)
{
	fpair_t	p;

	c.x *= scale;
	c.y *= scale;
	// Here for colission
	p.y = c.y - radius;
	while (p.y <= c.y + radius) // iterates a square where c.y is middle point
	{
		p.x = c.x - radius;
		while (p.x <= c.x + radius)
		{
			render_player(mmap, p, c, radius);
			p.x++;
		}
		p.y++;
	}
}

line_t	calculate_sensor(mmap_t *mmap, fpair_t start, double scale)
{
	line_t	d;

	d.start.x = start.x + mmap->player->dp.x * mmap->player->rad_size;
	d.start.y = start.y + mmap->player->dp.y * mmap->player->rad_size;
	d.end.x = start.x + mmap->player->dp.x * 30;
	d.end.y = start.y + mmap->player->dp.y * 30;
	d.start.x *= scale;
	d.start.y *= scale;
	d.end.x *= scale;
	d.end.y *= scale;
	d.delta.x = -(d.end.x - d.start.x);
	d.delta.y = -(d.end.y - d.start.y);
	d.steps = util_get_max(d.delta.x, d.delta.y);
	d.width.x = -mmap->player->dp.y;
	d.width.y = mmap->player->dp.x;
	// d.color = color_px(209, 107, 165, 255); // coolest color tho
	d.color = color_px(0, 0, 0, 255);
	return (d);
}

// d as data, n as new.
void	draw_sensor(mmap_t	*mmap, fpair_t start, double scale, line_t *d)
{
	fpair_t	n;
	fpair_t	inc;
	int		i;
	int		w;

	*d = calculate_sensor(mmap, start, scale);
	w = -2;
	while (++w <= 1)
	{
		n.x = d->start.x + d->width.x * (float) w;
		n.y = d->start.y + d->width.y * (float) w;
		inc.x = d->delta.x / d->steps;
		inc.y = d->delta.y / d->steps;
		i = d->steps;
		while (i--)
		{
			if (n.x >= 0&& n.x < mmap->img->width && \
				n.y >= 0 && n.y < mmap->img->height)
				mlx_put_pixel(mmap->img, n.x, n.y, d->color);
			n.x += inc.x;
			n.y += inc.y;
		}
	}
}
