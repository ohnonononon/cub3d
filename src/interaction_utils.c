/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:08:12 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/09 19:36:27 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	retrieve_tile(t_const c, t_map *map, t_fpair p, t_fpair mv)
{
	t_fpair	next;
	t_ipair	point;

	mv.x += 0.01;
	mv.y += 0.01;
	next.x = p.x + mv.x;
	next.y = p.y + mv.y;
	point.x = next.x + (c.pl_radius * 2);
	point.y = next.y;
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (0);
	point.x = next.x - (c.pl_radius * 2);
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (0);
	point.x = next.x;
	point.y = next.y + (2 * c.pl_radius);
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (0);
	point.y = next.y - (2 * c.pl_radius);
	if (map->grid[point.y / c.tile_size][point.x / c.tile_size] == '1')
		return (0);
	return (1);
}
