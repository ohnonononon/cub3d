/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/15 22:37:37 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Int.h"
#include <stdio.h>
#include <strings.h>

/* Referenced in /doc/colors.md as get_rgba */
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void* param)
{
	data_t	*d;
	d = (data_t *)param;

	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
}

int	check_px_limit_mmap(int x, int y, int limit)
{
	if (x < 0 || x > limit)
		return (0);
	if (y < 0 || y > limit)
		return (0);
	return (1);
}

void	paint_pixel_mmap(data_t *d, int x, int y, uint32_t color)
{
	paint_pixel_t	i;

	i.start_x = x * d->c.mmap_tile_side;
	i.start_y = y * d->c.mmap_tile_side;
	i.px = i.start_x;
	while (i.px < i.start_x + d->c.mmap_tile_side)
	{
		i.py = i.start_y;
		while (i.py < i.start_y + d->c.mmap_tile_side)
		{
			// if (check_px_limit_mmap(i.px, i.py, d->c.mmap_img_side))
			mlx_put_pixel(d->mmap.img, i.px, i.py, color);
			i.py++;
		}
		i.px++;
	}
}

void	draw_mmap(void	*ptr)
{
	data_t	*data = (data_t *)ptr;
	int32_t	color;
	int		i;

	i = 0;
	while (i < data->mapdata.size)
	{
		if (data->mapdata.map[i] == '1')
			color = ft_pixel(255, 0, 0, 120);
		else if (data->mapdata.map[i] == '0')
			color = ft_pixel(255, 255, 255, 120);
		else
			color = ft_pixel(255, 255, 0, 0);
		paint_pixel_mmap(data, i % data->mapdata.x, i / data->mapdata.x, color);
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
	mlx_loop_hook(d.mlx, draw_mmap, &d);
	mlx_loop(d.mlx);
	free(d.mapdata.map);
	free(d.mmap.pos_x);
	free(d.mmap.pos_y);
	return (mlx_terminate(d.mlx), EXIT_SUCCESS);
}
