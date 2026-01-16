/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:20:07 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/16 18:49:20 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"

void		set_constants(const_t *c);
int			set_mapdata(mapdata_t *d);
static int	set_mmap(data_t *d, const_t c);
static int	set_camera(data_t *d, int width, int height);
int			set_mlx(data_t	*d);

void	set_constants(const_t *c)
{
	c->mmap_padding = 1;
	c->mmap_tile_side = 27;
	c->mmap_img_side = c->mmap_tile_side * 7;
	c->tile_size = 64;
	c->height = c->tile_size * 9;
	c->width = c->tile_size * 16;
}

int	set_mapdata(mapdata_t *d)
{
	int	i;
	char	map[] = {
		'1', '1', '1', '1',
		'1', '0', '0', '1',
		'1', '0', '0', '1',
		'1', '1', '1', '1',
	};

	i = 0;
	d->x = 4;
	d->y = 4;
	d->size = d->x * d->y;
	d->map = calloc(d->size, sizeof(char));
	if (d->map == NULL)
		return (-1);
	while (i < d->size)
	{
		d->map[i] = map[i];
		i++;
	}
	return (0);
}

static int	set_mmap(data_t *d, const_t c)
{
	int	size;

	size = c.mmap_img_side + 1;
	if (!(d->mmap.img = mlx_new_image(d->mlx, size, size)))
	{
		mlx_close_window(d->mlx);
		return (-1);
	}
	if (mlx_image_to_window(d->mlx, d->mmap.img, c.width - size \
						 , c.height - size) == -1)
	{
		mlx_terminate(d->mlx);
		mlx_close_window(d->mlx);
		return (-1);
	}
	return (0);
}

static int	set_camera(data_t *d, int width, int height)
{
	if (!(d->cam.img = mlx_new_image(d->mlx, width, height)))
		return (-1);
	if (mlx_image_to_window(d->mlx, d->cam.img, 0, 0) == -1)
		return (-1);
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
	d->mlx = NULL;
	if (!(d->mlx = mlx_init(d->c.width, d->c.height, "CUB3D", true)))
		return (terminate_cub(d, &d->mmap, 1));
	d->cam.img = NULL;
	if (set_camera(d, d->c.width, d->c.height) == -1)
		return (terminate_cub(d, &d->mmap, 1));
	d->mmap.img = NULL;
	if (set_mmap(d, d->c) == -1)
		return (terminate_cub(d, &d->mmap, 1));
	return (0);
}
