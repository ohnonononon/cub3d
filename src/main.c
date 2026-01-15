/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/01/15 19:36:48 by ohnonon          ###   ########.fr       */
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

/* kept to study form and use */
void ft_randomize(void* param)
{
	data_t *d;

	d = (data_t *)param;
	for (uint32_t i = 0; i < d->img->width; ++i)
	{
		for (uint32_t y = 0; y < d->img->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(d->img, i, y, color);
		}
	}
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
			if (check_px_limit_mmap(i.px, i.py, d->c.mmap_img_side))
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

	color = ft_pixel(255, 255, 255, 255);
	for (int i = 0; i < data->mapdata.size; i++)
	{
		if (data->mapdata.map[i] == '1')
			color = ft_pixel(255, 0, 0, 120);
		else if (data->mapdata.map[i] == '0')
			color = ft_pixel(255, 255, 255, 120);
		paint_pixel_mmap(data, i % data->mapdata.x, i / data->mapdata.y, color);
	}
}

int	exit_err(void)
{
	printf("%s\n", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

int	set_mmap(data_t *d, const_t c)
{
	if (!(d->mmap.img = mlx_new_image(d->mlx, c.mmap_img_side, c.mmap_img_side)))
	{
		mlx_close_window(d->mlx);
		return (-1);
	}
	// if (mlx_image_to_window(d->mlx, d->mmap.img, WIDTH - MMAP_SIDE, 0) == -1)
	if (mlx_image_to_window(d->mlx, d->mmap.img, 0, c.height - c.mmap_img_side) == -1)
	{
		mlx_terminate(d->mlx);
		d->mlx = NULL;
		mlx_close_window(d->mlx);
		return (-1);
	}
	return (0);
}

/* Sets following elements:
	* Window
	* img 1: screen
	* img 2: minimap
	* pushes img to window
*/

int	set_mlx(data_t	*d)
{
	if (!(d->mlx = mlx_init(d->c.width, d->c.height, "CUB3D", true)))
		return (-1);
	if (set_mmap(d, d->c) == -1)
		return (-1);
	// if (!(d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT)))
	// {
	// 	mlx_close_window(d->mlx);
	// 	return (-1);
	// }
	// if (mlx_image_to_window(d->mlx, d->img, 0, 0) == -1)
	// {
	// 	mlx_close_window(d->mlx);
	// 	return (-1);
	// }
	return (0);
}

int	set_mapdata(mapdata_t *d)
{
	char	map[] = {
		'1', '1', '1', '1',
		'1', '0', '0', '1',
		'1', '0', '0', '1',
		'1', '1', '1', '1',
	};
	d->x = 4;
	d->y = 4;
	d->size = d->x * d->y;
	d->map = calloc(d->size, sizeof(char));
	if (d->map == NULL)
		return (-1);
	for (int i = 0; i < d->size; i++)
		d->map[i] = map[i];
	
	return (0);
}

void	set_constants(const_t *c)
{
	c->mmap_padding = 4;
	c->mmap_tile_side = 48;
	c->mmap_img_side = (c->mmap_padding * 2) + (c->mmap_tile_side * 10);
	c->tile_size = 64;
	c->height = c->tile_size * 9;
	c->width = c->tile_size * 16;
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
