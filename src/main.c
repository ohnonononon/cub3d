/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/16 19:10:16 by ohnonon          ###   ########.fr       */
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

void	render_mmap_player(mmap_t *map, player_t *pdata)
{
	(void)map;
	(void)pdata;
}

void	render_mmap(data_t *d, player_t	*pdata)
{
	int32_t	color;
	int		i;

	i = 0;
	while (i < d->mapdata.size)
	{
		color = set_color_mmap(d->mapdata.map[i]);
		paint_pixel_mmap(d, i % d->mapdata.x, i / d->mapdata.x, color);
		i++;
	}
	(void)pdata;
	// render_mmap_player(&d->mmap, pdata);
}

void	render_frame(void *ptr)
{
	data_t		*d;
	player_t	*pdata;

	d = (data_t *)ptr;
	pdata = &d->cam.player;
	// pdata->x = 100;
	// pdata->y = 100;
	//
	ft_hook(ptr);
	// update_cam();
	
	render_mmap(d, pdata);
	// render_view();
}

int	main(void)
{
	data_t	d = {0};

	if (set_mapdata(&d.mapdata) == -1)
		return (EXIT_SUCCESS);
	set_constants(&d.c);
	if (set_mlx(&d) == -1)
		return (terminate_cub(&d, -1));
	mlx_loop_hook(d.mlx, render_frame, &d);
	mlx_loop(d.mlx);
	return (terminate_cub(&d, 0));
}
