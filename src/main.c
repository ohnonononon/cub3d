/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/16 16:37:09 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Int.h"
#include <stdio.h>
#include <strings.h>

/* Referenced in /doc/colors.md as get_rgba */

void ft_hook(void* param)
{
	data_t	*d;
	d = (data_t *)param;

	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
}

void	handle_mmap(void	*ptr)
{
	data_t	*data = (data_t *)ptr;
	int32_t	color;
	int		i;

	i = 0;
	while (i < data->mapdata.size)
	{
		color = set_color(data->mapdata.map[i]);
		paint_pixel_mmap(data, i % data->mapdata.x, i / data->mapdata.x, color);
		paint_grid_mmap(data, i % data->mapdata.x, i / data->mapdata.x, color);
		i++;
	}
}

int	exit_err(void)
{
	printf("%s\n", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

int	main(void)
{
	data_t	d = {0};

	if (set_mapdata(&d.mapdata) == -1)
		return (EXIT_SUCCESS);
	set_constants(&d.c);
	if (set_mlx(&d) == -1)
		return (exit_err());
	mlx_loop_hook(d.mlx, ft_hook, &d);
	mlx_loop_hook(d.mlx, handle_mmap, &d);
	mlx_loop(d.mlx);
	free(d.mapdata.map);
	free(d.mmap.pos_x);
	free(d.mmap.pos_y);
	return (mlx_terminate(d.mlx), EXIT_SUCCESS);
}
