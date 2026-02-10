/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:45:40 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/10 15:30:04 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"

void debug_ray_line_2(char *buf, size_t bufsize,
					float dist_x, float dist_y,
					float delta_x, float delta_y,
					float ray_len)
{
	snprintf(buf, bufsize,
		  "Dist: (%.2f, %.2f)\n"
		  "Delta: (%.2f, %.2f)\n"
		  "ray_len: (%.2f)\n",
		  dist_x, dist_y,
		  delta_x, delta_y, ray_len
		  );
}

void debug_ray_line_1(char *buf, size_t bufsize,
					float player_x, float player_y,
					float ray_dx, float ray_dy,
					int tile_x, int tile_y,
					int step_x, int step_y)
{
	snprintf(buf, bufsize,
		  "Player: (%.2f, %.2f)\n"
		  "Ray: (%.2f, %.2f)\n"
		  "Tile: (%d, %d)\n"
		  "Step: (%d, %d)\n",
		  player_x, player_y,
		  ray_dx, ray_dy,
		  tile_x, tile_y,
		  step_x, step_y
	  );
}

void debug_player_line(char *buf, size_t bufsize,
					   float player_x, float player_y, float player_angle,
					   float line_end_x, float line_end_y)
{
	snprintf(buf, bufsize,
		  "Player: (%.2f, %.2f), Angle: %.2f rad"
		  "Line end: (%.2f, %.2f)",
		  player_x, player_y, player_angle,
		  line_end_x, line_end_y
		  );
}

void	print_dbg(t_data *d)
{
	char	b1[1024];
	t_ipair	i;

	i.y = (d->c.height / 10) ;
	i.x = (d->c.width / 48) * 1;

	if (d->debug != NULL)
	{
		mlx_delete_image(d->mlx, d->debug);
		d->debug = NULL;
	}
	if (d->d_flag == 0)
	{
		debug_player_line(b1, 264, d->player.p.x, d->player.p.y, \
					d->player.angle, \
					d->mmap.line.end.x, d->mmap.line.end.y);
		d->debug = mlx_put_string(d->mlx, b1, i.x, i.y);
		mlx_image_to_window(d->mlx, d->debug, 0, 0);
	}
	else if (d->d_flag == 1)
	{
		debug_ray_line_1(b1, 1024, d->player.p.x, d->player.p.y, d->cam.sun.ray.x, d->cam.sun.ray.y, d->cam.sun.tile.x, d->cam.sun.tile.y, d->cam.sun.step.x, d->cam.sun.step.y);
		d->debug = mlx_put_string(d->mlx, b1, i.x, i.y);
		mlx_image_to_window(d->mlx, d->debug, 0, 0);
	}
	else if (d->d_flag == 2)
	{
		debug_ray_line_2(b1, 1024, d->cam.sun.dist.x, d->cam.sun.dist.y, d->cam.sun.delta.x, d->cam.sun.delta.y, d->cam.sun.ray_len);
		d->debug = mlx_put_string(d->mlx, b1, i.x, i.y);
		mlx_image_to_window(d->mlx, d->debug, 0, 0);
	}

}

void	debug_config(t_data	d)
{
	printf("config ptrs:\n \
config struct	%p\n \
config.map	%p\n \
config.map.line	%p\n \
config.map.line[0]	%c\n \
config.map.height	%d\n", &d.config, d.config.map.grid, d.config.map.grid[0], d.config.map.grid[0][0], d.config.map.height);
}

void	debug_mmap(t_paint_pixel i, t_mmap *mmap)
{
	printf("i.start_x	%d\n \
i.start_y %d\n \
i.px	%d\n \
i.size	%d\n \
i.pad	%d\n \
mmap->img.h	%d\n \
mmap->img.w	%d\n \
", i.start_x, i.start_y, i.px, i.size, i.pad, mmap->img->height, mmap->img->width);
}
