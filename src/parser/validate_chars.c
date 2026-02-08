/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olreshet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by olreshet          #+#    #+#             */
/*   Updated: 2026/01/19 17:45:47 by olreshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int is_valid_char(char c)
{
	return (c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int is_start_pos(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void set_start_position(t_map *map, int j, int i, char c)
{
	map->start_x = j;
	map->start_y = i;
	map->start_dir = c;
}

static int check_char_and_count(t_map *map, int i, int j, int *start_count)
{
	if (!is_valid_char(map->grid[i][j]))
	{
		printf("Error\nInvalid character in map: '%c'\n",
			   map->grid[i][j]);
		return (0);
	}
	if (is_start_pos(map->grid[i][j]))
	{
		set_start_position(map, j, i, map->grid[i][j]);
		(*start_count)++;
	}
	return (1);
}

int validate_characters(t_map *map)
{
	int i;
	int j;
	int start_count;

	start_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (!check_char_and_count(map, i, j, &start_count))
				return (0);
			j++;
		}
		i++;
	}
	if (start_count != 1)
	{
		printf("Error\nMap must have exactly one starting position\n");
		return (0);
	}
	return (1);
}
