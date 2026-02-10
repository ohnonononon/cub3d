/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olreshet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:30:00 by olreshet          #+#    #+#             */
/*   Updated: 2026/02/10 20:58:03 by olreshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	parse_color(char *color_str, t_color *color);

static int	parse_texture_path(char *line, char **texture)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (0);
	path = ft_strdup(&line[i]);
	if (!path)
		return (0);
	j = ft_strlen(path) - 1;
	while (j >= 0 && ft_isspace(path[j]))
		path[j--] = '\0';
	if (access(path, F_OK) == -1)
	{
		printf("Error\nTexture file not found: %s\n", path);
		free(path);
		return (0);
	}
	*texture = path;
	return (1);
}

static int	parse_texture_identifier(char *line, t_textures *tex)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (tex->north)
			return (0);
		return (parse_texture_path(line + 3, &tex->north));
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (tex->south)
			return (0);
		return (parse_texture_path(line + 3, &tex->south));
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (tex->west)
			return (0);
		return (parse_texture_path(line + 3, &tex->west));
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (tex->east)
			return (0);
		return (parse_texture_path(line + 3, &tex->east));
	}
	return (-1);
}

static int	parse_color_identifier(char *line, t_textures *tex)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (tex->floor.r != -1)
			return (0);
		return (parse_color(line + 2, &tex->floor));
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (tex->ceiling.r != -1)
			return (0);
		return (parse_color(line + 2, &tex->ceiling));
	}
	return (-1);
}

int	parse_textures(char *line, t_textures *textures)
{
	int	result;

	result = parse_texture_identifier(line, textures);
	if (result != -1)
		return (result);
	result = parse_color_identifier(line, textures);
	if (result != -1)
		return (result);
	return (1);
}
