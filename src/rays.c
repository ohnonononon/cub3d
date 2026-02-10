/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:19:15 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/10 17:47:04 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calculate_main_ray(t_data *data);
void	ray_loop(t_ray *d, t_map *map);
void	set_ray_len(t_ray *d, int wall);
void	set_ray(t_ray *d, t_player *pl, t_const c);
void	set_ray_move(t_ray *d, t_player *pl, t_const c);

void	set_ray_move(t_ray *d, t_player *pl, t_const c)
{
	if (d->ray.x < 0 )
	{
		d->step.x = -1;
		d->dist.x = (pl->p.x - d->tile.x * c.tile_size) / c.tile_size \
			* d->delta.x;
	}
	else
	{
		d->step.x = 1;
		d->dist.x = ((d->tile.x + 1) * c.tile_size - pl->p.x) / c.tile_size \
			* d->delta.x;
	}
	if (d->ray.y < 0)
	{
		d->step.y = -1;
		d->dist.y = (pl->p.y - d->tile.y * c.tile_size)\
			/ c.tile_size * d->delta.y;
	}
	else
	{
		d->step.y = 1;
		d->dist.y = ((d->tile.y + 1) * c.tile_size - pl->p.y)\
			/ c.tile_size * d->delta.y;
	}
}

void	set_ray(t_ray *d, t_player *pl, t_const c)
{
	d->ray.x = cosf(pl->angle);
	d->ray.y = sinf(pl->angle);
	d->tile.x = (int)pl->p.x / c.tile_size;
	d->tile.y = (int)pl->p.y / c.tile_size;
	d->delta.x = fabsf(c.tile_size / d->ray.x);
	d->delta.y = fabsf(c.tile_size / d->ray.y);
	set_ray_move(d, pl, c);
}

// 0, vertical
void	set_ray_len(t_ray *d, int wall)
{
	if (wall == 1)
		d->ray_len = d->dist.y - d->delta.y;
	else
		d->ray_len = d->dist.x - d->delta.x;
}

void	ray_loop(t_ray *d, t_map *map)
{
	d->hit = 0;
	d->side = 0;
	while (!d->hit)
	{
		if (d->dist.x < d->dist.y)
		{
			d->dist.x += d->delta.x;
			d->tile.x += d->step.x;
			d->side = 0;
		}
		else
		{
			d->dist.y += d->delta.y;
			d->tile.y += d->step.y;
			d->side = 1;
		}
		if (map->grid[d->tile.y][d->tile.x] == '1')
			d->hit = 1;
	}
	set_ray_len(d, d->side);
}

void	calculate_main_ray(t_data *data)
{
	set_ray(&data->cam.sun, &data->player, data->c);
	ray_loop(&data->cam.sun, &data->config.map);
}
