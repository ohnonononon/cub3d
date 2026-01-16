/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:53:34 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/16 18:59:14 by ohnonon          ###   ########.fr       */
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

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/MLX42/include/MLX42/MLX42_Int.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h> //memset

typedef struct	player_s
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
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
	char	x;
	char	y;
}				mapdata_t;

typedef struct	mmap_s
{
	mlx_image_t	*img;
}				mmap_t;

/* HEIGHT and WIDTH are window related */
typedef struct	constants_s
{
	int	mmap_padding;
	int	mmap_tile_side;
	int	mmap_img_side;
	int	tile_size;
	int	height;
	int	width;
}				const_t;

typedef struct	camera_s
{
	mlx_image_t	*img;
	player_t	player;
}				cam_t;

typedef struct	data_s
{
	cam_t		cam;
	mapdata_t	mapdata;
	mmap_t		mmap;
	mlx_t		*mlx;
	const_t		c;
}				data_t;

/* SETUP */
void	set_constants(const_t *c);
int		set_mapdata(mapdata_t *d);
int		set_mlx(data_t	*d);

/* MMAP UTILS */
int32_t	set_color_mmap(char type);
void	paint_pixel_mmap(data_t *d, int x, int y, uint32_t color);

/* DRAW UTILS */
int32_t color_px(int32_t r, int32_t g, int32_t b, int32_t a);

void	ft_hook(void *param);

/* EXIT */
int	exit_err(void);
int	terminate_cub_ui(data_t *d, mmap_t *mmap, int err);
int	terminate_cub_data(data_t *d, int err);
int	terminate_cub(data_t *d, int err);

#endif
