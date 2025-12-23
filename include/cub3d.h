/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:53:34 by nimatura          #+#    #+#             */
/*   Updated: 2025/12/10 18:26:30 by ohnonon          ###   ########.fr       */
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

# ifndef WIDTH
#  define WIDTH 512
# endif
# ifndef HEIGHT
#  define HEIGHT 512
# endif
# ifndef BPP
#  define BPP 4
# endif
# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif


#include "../lib/MLX42/include/MLX42/MLX42.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



#include <string.h> //memset

typedef struct	data_s
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}				data_t;

int		ft_pixel(int r, int g, int b, int a);
void ft_randomize(void* param);
void ft_hook(void *param);

#endif
