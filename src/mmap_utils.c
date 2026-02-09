/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:31:23 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/09 01:30:33 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// static int	check_px_limit_mmap(int x, int y, int limit);
static int		is_padding(t_paint_pixel i);
int32_t			set_color_mmap(char type);

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
	else if (type == '0' || type == 'N' || type == 'E' || type == 'W' || type == 'S')
		color = color_px(95, 251, 241, 120);
	else
		color = color_px(209, 107, 165, 0);
	return (color);
}

static int	is_padding(t_paint_pixel i)
{
	return (i.px < i.start_x + i.pad || \
		 i.px >= i.start_x + i.size - i.pad || \
		 i.py < i.start_y + i.pad || \
		 i.py >= i.start_y + i.size - i.pad);
}

void	paint_pixel_mmap(t_mmap *mmap, t_const *c, t_ipair screen, uint32_t color)
{
	t_paint_pixel	i;

	(void)color;
	(void)mmap;
	i.start_x = screen.x * c->mmap_tile_side;
	i.start_y = screen.y * c->mmap_tile_side;
	i.px = i.start_x;
	i.size = c->mmap_tile_side;
	i.pad = c->mmap_padding;
	while (i.px < i.start_x + c->mmap_tile_side)
	{
		i.py = i.start_y;
		while (i.py < i.start_y + c->mmap_tile_side)
		{
			if (is_padding(i))
				mlx_put_pixel(mmap->img, i.px, i.py, color | 160);
			else
				mlx_put_pixel(mmap->img, i.px, i.py, color);
			i.py++;
		}
		i.px++;
	}
}
