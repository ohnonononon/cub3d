/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:20:07 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/14 03:09:47 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		set_data(int argc, char **argv, t_data *d);
void	set_player(t_map *map, t_player *d, t_const c);
void	set_constants(t_const *c);

void	set_player(t_map *map, t_player *d, t_const c)
{
	float	p;

	p = c.tile_size / 2.0;
	d->p.x = map->start_x * c.tile_size + p;
	d->p.y = map->start_y * c.tile_size + p;
	if (map->start_dir == 'N')
		d->angle = 1.57 * 3;
	else if (map->start_dir == 'E')
		d->angle = 0;
	else if (map->start_dir == 'W')
		d->angle = PI;
	else
		d->angle = 1.57;
	d->dp.x = cosf(d->angle);
	d->dp.y = sinf(d->angle);
}

void	set_constants(t_const *c)
{
	c->tile_size = 64;
	c->pl_radius = 8;
	c->height = c->tile_size * 9;
	c->width = c->tile_size * 16;
	c->eps = 0.0001f;
	c->fov = PI / 3.0f;
	c->proj_plane_dist = fabs(((float)c->width / 2.0) / \
tan(c->fov / 2.0));
}

int	set_data(int argc, char **argv, t_data *d)
{
	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (-1);
	}
	if (!parse_file(argv[1], &d->config))
	{
		printf("\n❌ PARSER FAILED\n");
		return (-1);
	}
	set_constants(&d->c);
	set_player(&d->config.map, &d->player, d->c);
	d->rays = malloc(sizeof(t_raydata) * d->c.width);
	if (d->rays == NULL)
		return (-1);
	if (set_mlx(d) == -1)
		return (terminate_cub(d, -1), -1);
	return (0);
}
