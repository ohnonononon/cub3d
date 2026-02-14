/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:20:07 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/14 03:47:51 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	set_camera_mlx(t_data *d, int width, int height)
{
	d->cam.img = mlx_new_image(d->mlx, width, height);
	if (!d->cam.img)
		return (-1);
	if (mlx_image_to_window(d->mlx, d->cam.img, 0, 0) == -1)
		return (-1);
	return (0);
}

int	load_texture_wrapper(mlx_image_t **img, mlx_texture_t **tex,
						char *path, mlx_t *mlx)
{
	*tex = mlx_load_png(path);
	if (!*tex)
		return (-1);
	*img = mlx_texture_to_image(mlx, *tex);
	if (!*img)
		return (-1);
	return (0);
}

int	set_textures(t_data *d, t_assets *ass, t_textures cf)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		ass->tex[i] = NULL;
		ass->img[i] = NULL;
		i++;
	}
	if (load_texture_wrapper(&ass->img[0], &ass->tex[0], \
							cf.east, d->mlx) == -1)
		return (-1);
	if (load_texture_wrapper(&ass->img[1], &ass->tex[1], \
							cf.south, d->mlx) == -1)
		return (-1);
	if (load_texture_wrapper(&ass->img[2], &ass->tex[2], \
							cf.west, d->mlx) == -1)
		return (-1);
	if (load_texture_wrapper(&ass->img[3], &ass->tex[3], \
							cf.north, d->mlx) == -1)
		return (-1);
	return (0);
}

int	set_mlx(t_data	*d)
{
	d->mlx = NULL;
	d->mlx = mlx_init(d->c.width, d->c.height, "CUB3D", true);
	if (!d->mlx)
		return (terminate_cub(d, 1));
	d->cam.img = NULL;
	if (set_camera_mlx(d, d->c.width, d->c.height) == -1)
		return (terminate_cub(d, 1));
	if (set_textures(d, &d->ass, d->config.textures) == -1)
		return (terminate_cub(d, 1));
	return (0);
}
