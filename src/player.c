/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:43:39 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/09 00:21:01 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"

static void	render_player(t_mmap *mmap, t_fpair p, t_fpair c, double radius)
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

void	draw_player(t_mmap *mmap, t_fpair c, int radius)
{
	t_fpair	p;

	c.x = mmap->in_pos.x;
	c.y = mmap->in_pos.y;
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
