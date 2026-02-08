/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olreshet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:45:00 by olreshet          #+#    #+#             */
/*   Updated: 2026/01/19 17:45:47 by olreshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void print_config(t_config *config)
{
	int i;

	printf("\n=== TEXTURE CONFIGURATION ===\n");
	printf("North texture: %s\n", config->textures.north ? config->textures.north : "NOT SET");
	printf("South texture: %s\n", config->textures.south ? config->textures.south : "NOT SET");
	printf("West texture:  %s\n", config->textures.west ? config->textures.west : "NOT SET");
	printf("East texture:  %s\n", config->textures.east ? config->textures.east : "NOT SET");
	printf("\nFloor color:   RGB(%d, %d, %d)\n",
		   config->textures.floor.r, config->textures.floor.g, config->textures.floor.b);
	printf("Ceiling color: RGB(%d, %d, %d)\n",
		   config->textures.ceiling.r, config->textures.ceiling.g, config->textures.ceiling.b);

	printf("\n=== MAP CONFIGURATION ===\n");
	printf("Map dimensions: %dx%d\n", config->map.width, config->map.height);
	printf("Starting position: (%d, %d)\n", config->map.start_x, config->map.start_y);
	printf("Starting direction: %c\n", config->map.start_dir);

	printf("\nMap grid:\n");
	i = 0;
	while (i < config->map.height)
	{
		printf("[%2d] %s\n", i, config->map.grid[i]);
		i++;
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	t_config config;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	printf("Testing parser with: %s\n", argv[1]);
	printf("=====================================\n");

	if (!parse_file(argv[1], &config))
	{
		printf("\n❌ PARSER FAILED\n");
		return (EXIT_FAILURE);
	}

	printf("\n✅ PARSER SUCCESS\n");
	print_config(&config);

	free_config(&config);
	return (EXIT_SUCCESS);
}
