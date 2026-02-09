/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olreshet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by olreshet          #+#    #+#             */
/*   Updated: 2026/02/08 19:05:37 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int validate_file_extension(const char *filename)
{
	size_t len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

void init_config(t_config *config)
{
	config->textures.north = NULL;
	config->textures.south = NULL;
	config->textures.west = NULL;
	config->textures.east = NULL;
	config->textures.floor.r = -1;
	config->textures.floor.g = -1;
	config->textures.floor.b = -1;
	config->textures.ceiling.r = -1;
	config->textures.ceiling.g = -1;
	config->textures.ceiling.b = -1;
	config->map.grid = NULL;
	config->map.width = 0;
	config->map.height = 0;
	config->map.start_x = -1;
	config->map.start_y = -1;
	config->map.start_dir = '\0';
}

char *read_line(int fd)
{
	char buffer[1024];
	char *line;
	int i;
	char c;
	ssize_t bytes;

	i = 0;
	bytes = read(fd, &c, 1);
	while (bytes > 0)
	{
		if (c == '\n')
			break;
		if (i < 1023)
			buffer[i++] = c;
		bytes = read(fd, &c, 1);
	}
	if (bytes <= 0 && i == 0)
		return (NULL);
	buffer[i] = '\0';
	line = ft_strdup(buffer);
	return (line);
}

int is_map_line(const char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int all_identifiers_present(t_config *config)
{
	if (!config->textures.north || !config->textures.south || !config->textures.west || !config->textures.east)
		return (0);
	if (config->textures.floor.r == -1 || config->textures.ceiling.r == -1)
		return (0);
	return (1);
}
