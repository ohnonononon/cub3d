/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:43:39 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/18 23:59:12 by ohnonon          ###   ########.fr       */
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
