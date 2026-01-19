/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olreshet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:30:00 by olreshet          #+#    #+#             */
/*   Updated: 2026/01/19 17:45:47 by olreshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int validate_characters(t_map *map);
int validate_closed_walls(t_map *map);

static void calculate_map_width(t_map *map)
{
	int i;
	int len;

	map->width = 0;
	i = 0;
	while (i < map->height)
	{
		len = ft_strlen(map->grid[i]);
		if (len > map->width)
			map->width = len;
		i++;
	}
}

static int validate_minimum_size(t_map *map)
{
	if (map->height < 3 || map->width < 3)
	{
		printf("Error\nMap must be at least 3x3 (including walls)\n");
		return (0);
	}
	return (1);
}

int validate_map(t_map *map)
{
	if (!map->grid || map->height == 0)
	{
		printf("Error\nNo map found\n");
		return (0);
	}
	calculate_map_width(map);
	if (!validate_minimum_size(map))
		return (0);
	if (!validate_characters(map))
		return (0);
	if (!validate_closed_walls(map))
		return (0);
	return (1);
}
