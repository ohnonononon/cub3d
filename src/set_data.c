/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:20:07 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/09 18:25:09 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_player(t_map *map, t_player *d, t_const c, t_mmap *mmap)
{
	float	p;

	p = c.tile_size / 2.0;
	mmap->player = d;
	d->p.x = map->start_x * c.tile_size + p;
	d->p.y = map->start_y * c.tile_size + p;
	if (map->start_dir == 'S')
		d->angle = 1.57;
	if (map->start_dir == 'E')
		d->angle = 0;
	if (map->start_dir == 'W')
		d->angle = PI;
	else
		d->angle = 1.57 * 3;
	d->dp.x = cosf(d->angle);
	d->dp.y = sinf(d->angle);
}

// mmap_scale corresponds to the % that 27 is of 64
// fov is measured also in radiants. 157 represents an angle of 90
// height: 576
// width: 1024 -> amount of rays!
void	set_constants(t_const *c)
{
	c->mmap_padding = 1;
	c->mmap_tile_line_count = 7;
	c->tile_size = 64;
	c->mmap_scale = 0.43;
	c->mmap_tile_side = 27;
	c->mmap_img_side = c->mmap_tile_side * c->mmap_tile_line_count;
	c->pl_radius = 8;
	c->height = c->tile_size * 9;
	c->width = c->tile_size * 16;
	c->eps = 0.0001f;
	c->fov = 157;
}

void	upd_mmap_data(t_mmap *mmap, t_const c, t_player *pl)
{
	mmap->size = c.mmap_img_side + 1;
	mmap->in_pos.x = pl->p.x * c.mmap_scale;
	mmap->in_pos.y = pl->p.y * c.mmap_scale;
}
