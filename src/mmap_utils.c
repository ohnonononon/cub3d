/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:31:23 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/16 16:39:21 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t	set_color(char type)
{
	int32_t	color;

	color = 0;
	if (type == '1')
		color = color_px(255, 0, 0, 120);
	else if (type == '0')
		color = color_px(255, 255, 255, 120);
	else
		color = color_px(255, 255, 0, 0);
	return (color);
}


int	check_px_limit_mmap(int x, int y, int limit)
{
	if (x < 0 || x > limit)
		return (0);
	if (y < 0 || y > limit)
		return (0);
	return (1);
}

void	paint_grid_mmap(data_t *d, int x, int y, uint32_t color)
{
	paint_pixel_t	i;

	i.start_x = x * d->c.mmap_tile_side;
	i.start_y = y * d->c.mmap_tile_side;
	i.px = i.start_x;
	while (i.px < i.start_x + d->c.mmap_padding)
	{
		i.py = i.start_y;
		while (i.py < i.start_y + d->c.mmap_padding)
		{
			if (check_px_limit_mmap(i.px, i.py, d->c.mmap_img_side))
				mlx_put_pixel(d->mmap.img, i.px, i.py, color);
			i.py++;
		}
		i.px++;
	}
}

void	paint_pixel_mmap(data_t *d, int x, int y, uint32_t color)
{
	paint_pixel_t	i;

	i.start_x = x * d->c.mmap_tile_side;
	i.start_y = y * d->c.mmap_tile_side;
	i.px = i.start_x;
	while (i.px < i.start_x + d->c.mmap_tile_side)
	{
		i.py = i.start_y;
		while (i.py < i.start_y + d->c.mmap_tile_side)
		{
			// if (check_px_limit_mmap(i.px, i.py, d->c.mmap_img_side))
			mlx_put_pixel(d->mmap.img, i.px, i.py, color);
			i.py++;
		}
		i.px++;
	}
}
