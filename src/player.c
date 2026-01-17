/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:43:39 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/17 14:44:25 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_player(player_t *d, cam_t *cam)
{
	(*cam).player = d;
	d->p.x = 85;
	d->p.y = 85;
}

static void	render_player(mmap_t *mmap, pair_t p, pair_t c, int radius)
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

void	draw_player(mmap_t *mmap, pair_t c, int radius)
{
	pair_t	p;

	p.y = c.y - radius;
	while (p.y <= c.y + radius)
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

