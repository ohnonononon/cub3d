/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olreshet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:50:00 by olreshet          #+#    #+#             */
/*   Updated: 2026/02/10 16:57:03 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* Parser structures */
typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_textures
{
	char *north;
	char *south;
	char *west;
	char *east;
	t_color floor;
	t_color ceiling;
} t_textures;

typedef struct s_map
{
	char **grid;
	int width;
	int height;
	int	size;
	int start_x;
	int start_y;
	char start_dir;
} t_map;

typedef struct s_config
{
	t_textures textures;
	t_map map;
} t_config;


/* Parser functions */
int		parse_file(const char *filename, t_config *config);
int		validate_file_extension(const char *filename);
int		validate_map(t_map *map);
int		parse_textures(char *line, t_textures *textures);
void	free_config(t_config *config);

/* Helper functions */
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char *s);
int		ft_isspace(int c);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);

/* parser gate */
int		load_map(int argc, char **argv, t_config *config);

#endif
