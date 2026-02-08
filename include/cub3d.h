/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:53:34 by nimatura          #+#    #+#             */
/*   Updated: 2025/12/29 16:46:00 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Permited functions:
 *
 * open, close, read, write,
printf, malloc, free, perror,
strerror, exit, gettimeofday.

• All functions of the math
library (-lm man man 3 math).

• gettimeofday()

• All functions of the MinilibX
library.

	*/

#ifndef CUB3D_H
# define CUB3D_H

# define TILE_SIZE 64
# define WIDTH 1024
# define HEIGHT 576

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/MLX42/include/MLX42/MLX42_Int.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

/* Parser structures */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_color	floor;
	t_color	ceiling;
}	t_textures;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		start_x;
	int		start_y;
	char	start_dir;
}	t_map;

typedef struct s_config
{
	t_textures	textures;
	t_map		map;
}	t_config;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			x;
	int			y;
	t_config	*config;
}	t_data;

/* Existing functions */
int		ft_pixel(int r, int g, int b, int a);
void	ft_randomize(void *param);
void	ft_hook(void *param);

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

#endif
