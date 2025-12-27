/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2025/12/27 13:31:51 by ohnonon          ###   ########.fr       */
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
	// if (mlx_is_key_down(d->mlx, MLX_KEY_K))
	// {
	// 	if (d->j < 20) /* if more than that, it segfaults */
	// 		d->j += 1;
	// }
	// if (mlx_is_key_down(d->mlx, MLX_KEY_J))
	// {
	// 	if (d->j > 0)
	// 		d->j -= 1;
	// }
	// // if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
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

static double	last_time = 0;

void	draw_basic_map(void	*ptr)
{
	data_t	*data = (data_t *)ptr;
	int	map[] = {
		1, 1, 1, 1,
		1, 0, 0, 1,
		1, 0, 0, 1,
		1, 1, 1, 1,
	};
	int	m_w = 4;
	int	m_h = 4;
	int32_t	color;

	color = ft_pixel(255, 255, 255, 255);
	for (int i = 0; i < m_w * m_h; ++i)
	{
		if (map[i] == 1)
			color = ft_pixel(255, 0, 0, 120);
		else if (map[i] == 0)
			color = ft_pixel(255, 255, 255, 120);
		paint_pixel(data, (data->x + i) % 4, (data->y + i) / 4, color);
	}
}

void	fps_loop(void *ptr)
{
	double	now = mlx_get_time();
	data_t	*data = (data_t *)ptr;
	if (now - last_time >= 2.0/30.0)
	{
		draw_basic_map(ptr);
		if (data->x < 16 && data->y < 16)
		{
			if (data->x % 4)
				data->x++;
			if (data->y / 3)
				data->y++;
		}
		else
		{
			data->x = 4;
			data->y = 4;
		}
		last_time = now;
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

	d.x = 4;
	d.y = 4;
	if (set_mlx(&d) == -1)
		return (exit_err());
	// mlx_loop_hook(d.mlx, ft_randomize, &d);
	mlx_loop_hook(d.mlx, ft_hook, &d);
	mlx_loop_hook(d.mlx, fps_loop, &d);
	mlx_loop(d.mlx);
	return (mlx_terminate(d.mlx), EXIT_SUCCESS);
}
