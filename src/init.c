/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:20:07 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/10 17:51:28 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include "parser.h"

int		set_mmap(t_data *d, t_const c);
int		set_camera(t_data *d, int width, int height);
int		set_mlx(t_data	*d);

int	set_mmap_mlx(t_data *d, t_const c)
{
	int	size;

	size = c.mmap_img_side + 1;
	if (!(d->mmap.img = mlx_new_image(d->mlx, size, size)))
		return (-1);
	if (mlx_image_to_window(d->mlx, d->mmap.img, c.width - size \
						 , c.height - size) == -1)
		return (-1);

	
	return (0);
}

int	set_camera_mlx(t_data *d, int width, int height)
{
	if (!(d->cam.img = mlx_new_image(d->mlx, width, height)))
		return (-1);
	if (mlx_image_to_window(d->mlx, d->cam.img, 0, 0) == -1)
		return (-1);
	return (0);
}

int	load_texture_wrapper(mlx_image_t *img, xpm_t *xpm, char *path, mlx_t *mlx)
{
	xpm = mlx_load_xpm42(path);
	if (!xpm)
		return (-1);
	img = mlx_texture_to_image(mlx, &xpm->texture);
	if (!img)
		return (-1);
	return (0);
}

int	set_textures(t_data *d, t_assets *ass, t_textures cf)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		ass->xpm[i] = NULL;
		ass->img[i] = NULL;
	}
	if (load_texture_wrapper(ass->img[0], ass->xpm[0], cf.east, d->mlx) == -1)
		return (-1);
	if (load_texture_wrapper(ass->img[1], ass->xpm[1], cf.south, d->mlx) == -1)
		return (-1);
	if (load_texture_wrapper(ass->img[2], ass->xpm[2], cf.west, d->mlx) == -1)
		return (-1);
	if (load_texture_wrapper(ass->img[3], ass->xpm[3], cf.north, d->mlx) == -1)
		return (-1);
	return (0);
}

int	set_mlx(t_data	*d)
{
	d->mlx = NULL;
	if (!(d->mlx = mlx_init(d->c.width, d->c.height, "CUB3D", true)))
		return (terminate_cub_ui(d, &d->mmap, 1));
	d->cam.img = NULL;
	if (set_camera_mlx(d, d->c.width, d->c.height) == -1)
		return (terminate_cub_ui(d, &d->mmap, 1));
	d->mmap.img = NULL;
	if (set_textures(d, &d->ass, d->config.textures) == -1)
		return (terminate_cub_ui(d, &d->mmap, 1));
	// if (set_mmap_mlx(d, d->c) == -1)
	// 	return (terminate_cub_ui(d, &d->mmap, 1));
	return (0);
}
