/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:53:34 by nimatura          #+#    #+#             */
/*   Updated: 2026/02/14 02:39:54 by ohnonon          ###   ########.fr       */
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

# include "parser.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <strings.h>
# include <math.h>
# include <string.h>

typedef enum e_or
{
    EAST,
    SOUTH,
    WEST,
    NORTH
}   e_or;

typedef struct	s_ipair
{
	int	x;
	int	y;
}				t_ipair;

typedef struct	s_fpair
{
	float	x;
	float	y;
}				t_fpair;
typedef struct	s_line
{
	t_fpair		start;
	t_fpair		end;
	t_fpair		delta;
	int			scale;
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

typedef struct s_tex_tools
{
	float		wall_x;
	float		angle;
	uint32_t	color;
	int			tex_x;
	int			tex_y;
	int			side;
	e_or		orient;
}		t_tex_tools;

typedef struct	s_const
{
	float	proj_plane_dist;
	float	eps;
	float	fov;
	int		pl_radius;
	int		tile_size;
	int		height;
	int		width;
}				t_const;

typedef struct	s_ray
{
	t_fpair	ray;
	t_ipair	tile;
	t_ipair	delta;
	t_ipair	step;
	t_fpair	dist;
	float	ray_len;
	int		side;
	int		hit;
}			t_ray;

typedef struct	s_raydata
{
	t_ray	ray;
	float	angle;
	float	len;
	int		side;
}			t_raydata;

typedef struct	s_vline
{
	float	wall_h;
	int		start_y;
	int		end_y;
	int		i;
}			t_vline;

typedef struct	s_camera
{
	mlx_image_t	*img;
	t_player	*player;
	t_ray		sun;
}				t_cam;

typedef struct	s_assets
{
	mlx_image_t		*img[4];
	mlx_texture_t	*tex[4];
	float			wall_x;
}				t_assets;

typedef struct	s_data
{
	mlx_t		*mlx;
	t_tex_tools	t;
	t_config	config;
	t_const		c;
	t_cam		cam;
	t_player	player;
	t_assets	ass;
	char		d_flag;
}				t_data;

/* MAIN */
void	program_loop(void *ptr);
int		set_data(int ac, char **av, t_data *d);

/* SETUP */
void	set_constants(t_const *c);
void	set_player(t_map *map, t_player *d, t_const c);

/* INIT */
int		set_camera_mlx(t_data *d, int width, int height);
int		load_texture_wrapper(mlx_image_t **img, mlx_texture_t **tex,
						 char *path, mlx_t *mlx);
int		set_textures(t_data *d, t_assets *ass, t_textures cf);
int		set_mlx(t_data	*d);

/* RAY CALCULATION */
void	set_ray_move(t_ray *d, t_player *pl, t_const c);
void	set_ray(t_ray *d, t_player *pl, t_const c);
void	calculate_main_ray(t_data *data);
void	ray_loop(t_ray *d, t_map *map);
void	set_ray_len(t_ray *d, int wall);

/* TEXTURE RENDERISATION */
uint32_t	get_tex_pixel(mlx_texture_t *tex, int x, int y);
void		set_tex(t_assets *ass, t_tex_tools *t, t_raydata *rd, t_player *pl);

/* CAMERA UTILS */
void	cam_bg(t_data *d);
float	normalize_angle(float start, int i, float angle_i);

/* INTERACTION UTILS: ex colision */
int		retrieve_tile(t_const c, t_map *map, t_fpair p, t_fpair mv);

/* DRAW UTILS */
int32_t color_px(int32_t r, int32_t g, int32_t b, int32_t a);

/* BUTTONS */
void	key_hooks(void *param);

/* EXIT */
int		exit_err(void);
int		terminate_cub_ui(t_data *d, int err);
int		terminate_cub_data(t_data *d, int err);
int		terminate_cub(t_data *d, int err);

#endif
