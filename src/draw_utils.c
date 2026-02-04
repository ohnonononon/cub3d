/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:33:12 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/19 00:03:10 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t color_px(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
/*
void	calculate_ray(mmap_t *mmap, fpair_t start, line_t *d)
{
	d->start.x = start.x + mmap->player->dp.x * mmap->player->rad_size;
	d->start.y = start.y + mmap->player->dp.y * mmap->player->rad_size;
	d->end.x = start.x + mmap->player->dp.x * 30;
	d->end.y = start.y + mmap->player->dp.y * 30;
	d->start.x *= scale;
	d->start.y *= scale;
	d->end.x *= scale;
	d->end.y *= scale;
	d->delta.x = -(d->end.x - d->start.x);
	d->delta.y = -(d->end.y - d->start.y);
	d->draw.steps = util_get_max(d->delta.x, d->delta.y);
	d->draw.thick.x = -mmap->player->dp.y;
	d->draw.thick.y = mmap->player->dp.x;
	d->draw.color = color_px(0, 0, 0, 255);
	// d.color = color_px(209, 107, 165, 255); // coolest color tho
	d->draw.color = color_px(0, 0, 0, 255);
	w = -2;
	while (++w <= 1)
	{
		pos.x = d->start.x + d->width.x * (float) w;
		pos.y = d->start.y + d->width.y * (float) w;
		inc.x = d->delta.x / d->steps;
		inc.y = d->delta.y / d->steps;
		i = d->steps;
		while (i--)
		{
			if (pos.x >= 0&& pos.x < mmap->img->width && \
				pos.y >= 0 && pos.y < mmap->img->height)
				mlx_put_pixel(mmap->img, pos.x, pos.y, d->color);
			pos.x += inc.x;
			pos.y += inc.y;
		}
	}
}
*/
