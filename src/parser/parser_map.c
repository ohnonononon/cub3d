/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olreshet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by olreshet          #+#    #+#             */
/*   Updated: 2026/01/19 17:45:47 by olreshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char *read_line(int fd);

int store_first_map_line(t_config *config, char *trimmed)
{
	config->map.grid = malloc(sizeof(char *) * 2);
	if (!config->map.grid)
		return (0);
	config->map.grid[0] = ft_strdup(trimmed);
	config->map.grid[1] = NULL;
	return (1);
}

int parse_texture_line(char *line, char *trimmed, t_config *config)
{
	int result;

	result = parse_textures(trimmed, &config->textures);
	free(trimmed);
	if (!result)
		free(line);
	return (result);
}

static int count_existing_lines(t_config *config)
{
	int count;

	count = 0;
	if (config->map.grid)
	{
		while (config->map.grid[count])
			count++;
	}
	return (count);
}

static int add_line_to_map(t_config *config, char *trimmed, int count)
{
	char **temp;
	int i;

	temp = malloc(sizeof(char *) * (count + 2));
	if (!temp)
		return (0);
	i = 0;
	while (i < count)
	{
		temp[i] = config->map.grid[i];
		i++;
	}
	temp[count] = trimmed;
	temp[count + 1] = NULL;
	if (config->map.grid)
		free(config->map.grid);
	config->map.grid = temp;
	return (1);
}

int store_map_lines(int fd, t_config *config)
{
	char *line;
	char *trimmed;
	int count;

	count = count_existing_lines(config);
	line = read_line(fd);
	while (line != NULL)
	{
		trimmed = ft_strtrim(line);
		if (trimmed && trimmed[0] != '\0')
		{
			if (!add_line_to_map(config, trimmed, count))
			{
				free(line);
				return (0);
			}
			count++;
		}
		else
			free(trimmed);
		free(line);
		line = read_line(fd);
	}
	config->map.height = count;
	return (1);
}
