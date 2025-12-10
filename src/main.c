/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2025/12/10 16:20:59 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#define WIDTH 512
#define HEIGHT 512

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

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
	data_t* d;
	d = (data_t *)param;

	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
	if (mlx_is_key_down(d->mlx, MLX_KEY_UP))
		d->img->instances[0].y -= 5;
	if (mlx_is_key_down(d->mlx, MLX_KEY_DOWN))
		d->img->instances[0].y += 5;
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
		d->img->instances[0].x -= 5;
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
		d->img->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

void	render_basic_map()
{


}

int	main(void)
{
	data_t	d = {0};

	// Creates d.mlx api agent: Implies creation of window
	if (!(d.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// Creates an d.img canvas in window
	if (!(d.img = mlx_new_image(d.mlx, 128, 128)))
	{
		mlx_close_window(d.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// // Use d.img to draw
	memset(d.img->pixels, 255, d.img->width * d.img->height * sizeof(int32_t));
	if (mlx_image_to_window(d.mlx, d.img, 0, 0) == -1)
	{
		mlx_close_window(d.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	//
	// // mlx_loop_hook(d.mlx, ft_randomize, d.mlx);
	mlx_loop_hook(d.mlx, ft_hook, &d);
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);
	return (EXIT_SUCCESS);
}
