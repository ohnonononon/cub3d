/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:53:34 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/17 21:05:48 by ohnonon          ###   ########.fr       */
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

# ifndef PI
#  define PI 3.14159265
# endif
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/MLX42/include/MLX42/MLX42_Int.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <math.h>

#include <string.h> //memset

typedef struct	ipair_s
{
	int	x;
	int	y;
}				ipair_t;

typedef struct	dpair_s
{
	double	x;
	double	y;
}				dpair_t;

typedef struct	fpair_s
{
	float	x;
	float	y;
}				fpair_t;

typedef struct	line_s
{
	fpair_t	start;
	fpair_t	end;
	fpair_t	delta;
	int		steps;
	int		scale;
}				line_t;

typedef struct	player_s
{
	line_t	line;
	fpair_t	p;
	fpair_t	dp;
	float	angle;
	int		rad_size;
}				player_t;

typedef struct	paint_pixel_s
{
	int	start_x;
	int	px;
	int	start_y;
	int	py;
	int	size;
	int	pad;
}				paint_pixel_t;

typedef struct	mapdata_s
{
	char	*map;
	int		size;
	fpair_t	player_pos;
	char	x;
	char	y;
}				mapdata_t;

typedef struct	mmap_s
{
	mlx_image_t	*img;
	double		side;
	player_t	*player;
}				mmap_t;

/* HEIGHT and WIDTH are window related */
typedef struct	constants_s
{
	int	mmap_padding;
	int	mmap_tile_side;
	int	mmap_img_side;
	int	mmap_tile_line_count;
	double	mmap_scale;
	int	pl_radius;
	int	tile_size;
	int	height;
	int	width;
}				const_t;

typedef struct	camera_s
{
	mlx_image_t	*img;
	player_t	*player;
}				cam_t;

typedef struct	data_s
{
	mapdata_t	mapdata;
	const_t		c;
	mlx_t		*mlx;
	cam_t		cam;
	mmap_t		mmap;
	player_t	player;
	mlx_image_t	*debug;
}				data_t;

/* MAIN */
void	display(void *ptr);

/* SETUP */
void	set_constants(const_t *c);
int		set_mapdata(mapdata_t *d);
int		set_mlx(data_t	*d);

/* PLAYER */
void	set_player(player_t *d, cam_t *cam, mmap_t *mmap);
void	draw_sensor(mmap_t	*mmap, fpair_t start, double scale, line_t *d);
void	draw_player(mmap_t *mmap, fpair_t c, int radius, double scale);

/* MMAP UTILS */
int32_t	set_color_mmap(char type);
void	paint_pixel_mmap(data_t *d, int x, int y, uint32_t color);

/* DRAW UTILS */
int32_t color_px(int32_t r, int32_t g, int32_t b, int32_t a);

/* BUTTONS */
void	key_hooks(void *param);

/* EXIT */
int	exit_err(void);
int	terminate_cub_ui(data_t *d, mmap_t *mmap, int err);
int	terminate_cub_data(data_t *d, int err);
int	terminate_cub(data_t *d, int err);

/* MATH UTLS */

int util_roundf(float x);
int	util_get_max(float a, float b);

/* DEBUG */
void	debug_player_line(char *buf, size_t bufsize,
					   float player_x, float player_y, float player_angle,
					   float line_end_x, float line_end_y);
void	print_dbg(data_t *d);

#endif
