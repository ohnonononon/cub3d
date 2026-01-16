/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:31:23 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/16 20:52:55 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// static int	check_px_limit_mmap(int x, int y, int limit);
static int		is_padding(paint_pixel_t i);
int32_t			set_color_mmap(char type);
void			paint_pixel_mmap(data_t *d, int x, int y, uint32_t color);

/* Colors
*
* Wall == 1
* Floor == 0/WSNE
* Space == other
*/
int32_t	set_color_mmap(char type)
{
	int32_t	color;

	color = 0;
	if (type == '1')
		color = color_px(134, 168, 231, 120);
	else if (type == '0')
		color = color_px(95, 251, 241, 120);
	else
		color = color_px(209, 107, 165, 120);
	return (color);
}
static int	is_padding(paint_pixel_t i)
{
	return (i.px < i.start_x + i.pad || \
		 i.px >= i.start_x + i.size - i.pad || \
		 i.py < i.start_y + i.pad || \
		 i.py >= i.start_y + i.size - i.pad);
}

void	paint_pixel_mmap(data_t *d, int x, int y, uint32_t color)
{
	paint_pixel_t	i;

	i.start_x = x * d->c.mmap_tile_side;
	i.start_y = y * d->c.mmap_tile_side;
	i.px = i.start_x;
	i.size = d->c.mmap_tile_side;
	i.pad = d->c.mmap_padding;
	while (i.px < i.start_x + d->c.mmap_tile_side)
	{
		i.py = i.start_y;
		while (i.py < i.start_y + d->c.mmap_tile_side)
		{
			if (is_padding(i))
				mlx_put_pixel(d->mmap.img, i.px, i.py, color | 160);
			else
				mlx_put_pixel(d->mmap.img, i.px, i.py, color);
			i.py++;
		}
		i.px++;
	}
}

/*
static int	check_px_limit_mmap(int x, int y, int limit)
{
	if (x < 0 || x > limit)
		return (0);
	if (y < 0 || y > limit)
		return (0);
	return (1);
}*/
