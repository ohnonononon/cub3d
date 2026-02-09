/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:53:34 by nimatura          #+#    #+#             */
/*   Updated: 2026/02/09 19:10:22 by ohnonon          ###   ########.fr       */
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

#include "parser.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <math.h>
#include <string.h> //memset

typedef struct	s_ipair
{
	int	x;
	int	y;
}				t_ipair;

typedef struct	s_dpair
{
	double	x;
	double	y;
}				t_dpair;

typedef struct	s_fpair
{
	float	x;
	float	y;
}				t_fpair;

typedef struct	s_draw
{
	t_fpair	thick;
	int32_t	color;
	int		steps;
}				t_draw;

typedef struct	s_line
{
	t_fpair		start;
	t_fpair		end;
	t_fpair		delta;
	int			scale;
	t_draw		draw;
}				t_line;

typedef struct	s_player
{
	t_fpair	p;
	t_fpair	dp;
	float	angle;
	int		rad_size;
}				t_player;

typedef struct	s_paint_pixel
{
	int	start_x;
	int	px;
	int	start_y;
	int	py;
	int	size;
	int	pad;
}				t_paint_pixel;

typedef struct	s_mapdata
{
	char	*map;
	int		size;
	t_fpair	player_pos;
	char	x;
	char	y;
}				t_mapdata;

typedef struct	s_mmap
{
	mlx_image_t	*img;
	double		side;
	int			size;
	t_fpair		in_pos;
	t_player	*player;
	t_line		line;
}				t_mmap;

/* HEIGHT and WIDTH are window related */
typedef struct	s_const
{
	int	mmap_padding;
	int	mmap_tile_side;
	int	mmap_img_side;
	int	mmap_tile_line_count;
	double	mmap_scale;
	float	eps;
	int	pl_radius;
	int	tile_size;
	int	height;
	int	width;
	int	fov;
}				t_const;

typedef struct	s_ray
{
	t_fpair	ray;
	t_ipair	tile;
	t_ipair	delta;
	t_ipair	step;
	t_fpair	dist;
	float	ray_len;
}			t_ray;

typedef struct	s_camera
{
	mlx_image_t	*img;
	t_player	*player;
	t_ray		sun;
}				t_cam;

typedef struct	s_data
{
	mlx_t		*mlx;
	t_config	config;
	t_const		c;
	t_cam		cam;
	t_mmap		mmap;
	t_player	player;
	mlx_image_t	*debug;
	char		d_flag;
}				t_data;

/* MAIN */
void	program_loop(void *ptr);

/* SETUP */
void	set_constants(t_const *c);
int		set_mapdata(t_mapdata *d);
int		set_mlx(t_data	*d);

/* INTERACTION UTILS: ex colision */
int		retrieve_tile(t_const c, t_map *map, t_fpair p, t_fpair mv);

/* PLAYER */
void	set_player(t_map *map, t_player *d, t_const c, t_mmap *mmap);
void	draw_player(t_mmap *mmap, t_fpair c, int radius);

/* MINIMAP */
void	upd_mmap_data(t_mmap *mmap, t_const c, t_player *pl);
void	render_mmap(t_cam *cam, t_mmap *mmap, t_const *c, t_map *map);
void	draw_line_mmap(mlx_image_t *img, t_fpair start, t_fpair delta, t_draw draw);
void	calculate_line_mmap(t_cam *cam, t_player *p, t_line *line, t_const c);

/* MMAP UTILS */
int32_t	set_color_mmap(char type);
void	paint_pixel_mmap(t_mmap *mmap, t_const *c, t_ipair screen, uint32_t color);

/* DRAW UTILS */
int32_t color_px(int32_t r, int32_t g, int32_t b, int32_t a);

/* BUTTONS */
void	key_hooks(void *param);

/* EXIT */
int		exit_err(void);
int		terminate_cub_ui(t_data *d, t_mmap *mmap, int err);
int		terminate_cub_data(t_data *d, int err);
int		terminate_cub(t_data *d, int err);

/* MATH UTLS */
int		util_roundf(float x);
int		util_get_max(float a, float b);

/* DEBUG */
void	debug_player_line(char *buf, size_t bufsize,
					   float player_x, float player_y, float player_angle,
					   float line_end_x, float line_end_y);
void	print_dbg(t_data *d);

/* RAY CALCULATION */
void	set_ray_move(t_ray *d, t_player *pl, t_const c);
void	set_ray(t_ray *d, t_player *pl, t_const c);
void	calculate_main_ray(t_data *data);
void	ray_loop(t_ray *d, t_map *map);
void	set_ray_len(t_ray *d, int wall);

/* THROTTLE */
int	throttle_fps(void);

#endif
