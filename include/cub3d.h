/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:53:34 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/15 19:33:16 by ohnonon          ###   ########.fr       */
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

# ifndef MMAP_PADDING
# endif

# ifndef MMAP_TILE_SIDE
# endif

# ifndef MMAP_SIDE
# endif

# ifndef TILE_SIZE
# endif

# ifndef HEIGHT
# endif

# ifndef WIDTH
# endif

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/MLX42/include/MLX42/MLX42_Int.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h> //memset

typedef struct	paint_pixel_s
{
	int	start_x;
	int	px;
	int	start_y;
	int	py;
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
	int32_t		*pos_x;
	int32_t		*pos_y;
}				mmap_t;

typedef struct	constants_s
{
	int	mmap_padding;
	int	mmap_tile_side;
	int	mmap_img_side;
	int	tile_size;
	int	height;
	int	width;
}				const_t;

typedef struct	data_s
{
	mapdata_t	mapdata;
	mmap_t		mmap;
	mlx_t		*mlx;
	mlx_image_t	*img;
	const_t		c;
}				data_t;

int		ft_pixel(int r, int g, int b, int a);
void ft_randomize(void* param);
void ft_hook(void *param);

#endif
