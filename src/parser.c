/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olreshet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:30:00 by olreshet          #+#    #+#             */
/*   Updated: 2026/02/10 20:39:55 by olreshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	init_config(t_config *config);
char	*read_line(int fd);
int		is_map_line(const char *line);
int		store_map_lines(int fd, t_config *config);
int		store_first_map_line(t_config *config, char *trimmed);
int		parse_texture_line(char *line, char *trimmed, t_config *config);
int		all_identifiers_present(t_config *config);

static int	handle_map_start(t_config *config, char *trimmed, char *line)
{
	if (!all_identifiers_present(config))
	{
		printf("Error\nMissing texture or color identifier\n");
		free(trimmed);
		free(line);
		return (0);
	}
	if (!store_first_map_line(config, trimmed))
	{
		free(trimmed);
		free(line);
		return (0);
	}
	free(trimmed);
	free(line);
	return (1);
}

static int	parse_config_lines(int fd, t_config *config)
{
	char	*line;
	char	*trimmed;

	line = read_line(fd);
	while (line != NULL)
	{
		trimmed = ft_strtrim(line);
		if (trimmed && trimmed[0] != '\0')
		{
			if (is_map_line(trimmed))
			{
				if (!handle_map_start(config, trimmed, line))
					return (0);
				break ;
			}
			if (!parse_texture_line(line, trimmed, config))
				return (0);
		}
		else
			free(trimmed);
		free(line);
		line = read_line(fd);
	}
	return (1);
}

static int	open_and_validate_file(const char *filename)
{
	int	fd;

	if (!validate_file_extension(filename))
	{
		printf("Error\nInvalid file extension (must be .cub)\n");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("Error\nFailed to open file");
	return (fd);
}

static int	parse_file_content(int fd, t_config *config)
{
	if (!parse_config_lines(fd, config))
		return (0);
	if (!store_map_lines(fd, config))
		return (0);
	return (1);
}

int	parse_file(const char *filename, t_config *config)
{
	int	fd;

	fd = open_and_validate_file(filename);
	if (fd < 0)
		return (0);
	init_config(config);
	if (!parse_file_content(fd, config))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (validate_map(&config->map));
}
