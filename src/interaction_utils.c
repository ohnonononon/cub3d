/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:08:12 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/11 20:07:16 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_diag_touch(t_const c, t_map *map, t_fpair p, t_fpair mv)
{
	t_fpair	next;
	t_ipair	point;

	next.x = p.x + mv.x - 0.1;
	next.y = p.y + mv.y - 0.1;
	point.x = next.x + c.pl_radius;
	point.y = next.y - c.pl_radius;
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (1);
	point.x = next.x - c.pl_radius;
	point.y = next.y - c.pl_radius;
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (1);
	point.x = next.x + c.pl_radius;
	point.y = next.y + c.pl_radius;
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (1);
	point.x = next.x - c.pl_radius;
	point.y = next.y + c.pl_radius;
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (1);
	return (0);
}


static int	is_cardinal_touch(t_const c, t_map *map, t_fpair p, t_fpair mv)
{
	t_fpair	next;
	t_ipair	point;

	next.x = p.x + mv.x + 0.1;
	next.y = p.y + mv.y + 0.1;
	point.x = next.x + c.pl_radius;
	point.y = next.y;
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (1);
	point.x = next.x - c.pl_radius;
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (1);
	point.x = next.x;
	point.y = next.y + c.pl_radius;
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (1);
	point.y = next.y - c.pl_radius;
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (1);
	return (0);
}

int	retrieve_tile(t_const c, t_map *map, t_fpair p, t_fpair mv)
{
	if (is_diag_touch(c, map, p, mv))
		return (0);
	if (is_cardinal_touch(c, map, p, mv))
		return (0);
	return (1);
}
