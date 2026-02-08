/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olreshet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by olreshet          #+#    #+#             */
/*   Updated: 2026/01/19 17:45:47 by olreshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int check_cell_closed(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(map->grid[y]))
		return (0);
	if (map->grid[y][x] == ' ')
		return (0);
	if (map->grid[y][x] == '\0')
		return (0);
	return (1);
}

static int is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int check_cell_walls(t_map *map, int i, int j)
{
	if (!check_cell_closed(map, i - 1, j) || !check_cell_closed(map, i + 1, j) || !check_cell_closed(map, i, j - 1) || !check_cell_closed(map, i, j + 1))
	{
		printf("Error\nMap is not closed by walls at (%d, %d)\n",
			   j, i);
		return (0);
	}
	return (1);
}

int validate_closed_walls(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (is_walkable(map->grid[i][j]))
			{
				if (!check_cell_walls(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
