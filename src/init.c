/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:20:07 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/15 22:54:22 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_constants(const_t *c)
{
	c->mmap_padding = 4;
	c->mmap_tile_side = 27;
	c->mmap_img_side = (c->mmap_tile_side * 7);
	c->tile_size = 64;
	c->height = c->tile_size * 9;
	c->width = c->tile_size * 16;
}

int	set_mapdata(mapdata_t *d)
{
	char	map[] = {
		'1', '1', '1', '1',
		'1', '0', '0', '1',
		'1', '0', '0', '1',
		'1', '1', '1', '1',
	};
	d->x = 4;
	d->y = 4;
	d->size = d->x * d->y;
	d->map = calloc(d->size, sizeof(char));
	if (d->map == NULL)
		return (-1);
	for (int i = 0; i < d->size; i++)
		d->map[i] = map[i];
	
	return (0);
}

int	set_mmap(data_t *d, const_t c)
{
	if (!(d->mmap.img = mlx_new_image(d->mlx, 190, 190)))
	{
		mlx_close_window(d->mlx);
		return (-1);
	}
	if (mlx_image_to_window(d->mlx, d->mmap.img, c.width - 190, c.height - 190) == -1)
	{
		mlx_terminate(d->mlx);
		d->mlx = NULL;
		mlx_close_window(d->mlx);
		return (-1);
	}
	return (0);
}

/* Sets following elements:
	* Window
	* img 1: screen
	* img 2: minimap
	* pushes img to window
*/
int	set_mlx(data_t	*d)
{
	if (!(d->mlx = mlx_init(d->c.width, d->c.height, "CUB3D", true)))
		return (-1);
	if (set_mmap(d, d->c) == -1)
		return (-1);
	// if (!(d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT)))
	// {
	// 	mlx_close_window(d->mlx);
	// 	return (-1);
	// }
	// if (mlx_image_to_window(d->mlx, d->img, 0, 0) == -1)
	// {
	// 	mlx_close_window(d->mlx);
	// 	return (-1);
	// }
	return (0);
}

