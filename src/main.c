/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/17 16:17:14 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Int.h"
#include <stdio.h>
#include <strings.h>

void ft_hook(void* param)
{
	data_t	*d;
	d = (data_t *)param;

	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
}
#include <math.h>

// void handle_mmap_moving(t_data *d)
// {
//     int px, py;
//     int player_radius = 3;        // radius in minimap pixels
//     uint32_t player_color = 0xFF0000FF; // ARGB: opaque red
//
//     // Clear minimap first (optional: fill with background)
//     for (int y = 0; y < d->mmap_height; y++)
//     {
//         for (int x = 0; x < d->mmap_width; x++)
//             mlx_put_pixel(d->mmap, x, y, 0x00000000); // transparent / black
//     }
//
// }

// iterates on the ammount of tiles
void	render_mmap(data_t *d, player_t	*pl)
{
	static pair_t	c;
	int32_t			color;
	// int				y;
	int				i;

	// y = 0;
	(void)pl;
	i = 0;
	while (i < d->mapdata.size)
	{
		color = set_color_mmap(d->mapdata.map[i]);
		paint_pixel_mmap(d, i % d->mapdata.x, i / d->mapdata.x, color);
		i++;
	}
	c.x = (int)(d->player.p.x * d->c.mmap_scale);
	c.y = (int)(d->player.p.y * d->c.mmap_scale);
	draw_player(&d->mmap, c, d->c.pl_radius);
}

void	display(void *ptr)
{
	data_t		*d;

	d = (data_t *)ptr;
	ft_hook(ptr);
	// update_cam();
	
	render_mmap(d, &d->player);
	// render_view(); no existe porque no hace falta pintarlo.
}

int	main(void)
{
	data_t	d = {0};

	if (set_mapdata(&d.mapdata) == -1)
		return (EXIT_SUCCESS);
	set_constants(&d.c);
	set_player(&d.player, &d.cam);
	if (set_mlx(&d) == -1)
		return (terminate_cub(&d, -1));
	// if (set_player(&d.player, &d.cam) == -1)
	// 	return (terminate_cub(&d, -1));

	mlx_key_hook(d.mlx, &buttons, &d);
	mlx_loop_hook(d.mlx, display, &d);
	mlx_loop(d.mlx);
	return (terminate_cub(&d, 0));
}
