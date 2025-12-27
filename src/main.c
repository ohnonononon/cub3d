/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2025/12/23 11:40:21 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

/* commented lines move the canvas of the img, potential break there */
void ft_hook(void* param)
{
	data_t	*d;
	d = (data_t *)param;

	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
	// if (mlx_is_key_down(d->mlx, MLX_KEY_UP))
	// 	d->img->instances[0].y -= 5;
	// if (mlx_is_key_down(d->mlx, MLX_KEY_DOWN))
	// 	d->img->instances[0].y += 5;
	// if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
	// 	d->img->instances[0].x -= 5;
	// if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
	// 	d->img->instances[0].x += 5;
}

void	paint_pixel(data_t *d, int x, int y, uint32_t color)
{
	int	start_x;
	int	px;
	int	start_y;
	int	py;

	start_x = x * TILE_SIZE;
	start_y = y * TILE_SIZE;
	px = start_x;
	while (px < start_x + TILE_SIZE)
	{
		py = start_y;
		while (py < start_y + TILE_SIZE)
		{
			mlx_put_pixel(d->img, px, py, color);
			py++;
		}
		px++;
	}
}

void	draw_basic_map(data_t	*data)
{
	int	map[] = {
		1, 1, 1, 1,
		1, 0, 0, 1,
		1, 0, 0, 1,
		1, 1, 1, 1,
		};
	int	m_w = 4;
	int	m_h = 4;
	int	i = 0;
	int32_t	color;

	color = ft_pixel(255, 255, 255, 255);
	while (i < m_w * m_h)
	{
		if (map[i] == 1)
			color = ft_pixel(255, 0, 0, 120);
		else if (map[i] == 0)
			color = ft_pixel(255, 255, 255, 120);
		paint_pixel(data, i % 4, i / 4, color);
		i++;
	}
}

int	exit_err(void)
{
	printf("%s\n", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

int	set_mlx(data_t	*d)
{
	if (!(d->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (-1);
	if (!(d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(d->mlx);
		return (-1);
	}
	if (mlx_image_to_window(d->mlx, d->img, 0, 0) == -1)
	{
		mlx_close_window(d->mlx);
		return (-1);
	}
	return (1);
}

int	main(void)
{
	data_t	d = {0};

	if (set_mlx(&d) == -1)
		return (exit_err());
	draw_basic_map(&d);
	// mlx_loop_hook(d.mlx, ft_randomize, &d);
	mlx_loop_hook(d.mlx, ft_hook, &d);
	mlx_loop(d.mlx);
	return (mlx_terminate(d.mlx), EXIT_SUCCESS);
}
