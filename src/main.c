/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/16 18:59:22 by ohnonon          ###   ########.fr       */
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

void	render_mmap(data_t *data)
{
	int32_t	color;
	int		i;

	i = 0;
	while (i < data->mapdata.size)
	{
		color = set_color_mmap(data->mapdata.map[i]);
		paint_pixel_mmap(data, i % data->mapdata.x, i / data->mapdata.x, color);
		i++;
	}
}

void	render_frame(void *ptr)
{
	data_t	*data = (data_t *)ptr;

	ft_hook(ptr);
	// update_cam();
	
	render_mmap(data);
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
