/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:20:07 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/08 23:36:05 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"

int		set_mmap(t_data *d, t_const c);
int		set_camera(t_data *d, int width, int height);
int		set_mlx(t_data	*d);

// BUG: Check mlx fail case
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

// BUG: Check mlx fail case
int	set_camera_mlx(t_data *d, int width, int height)
{
	if (!(d->cam.img = mlx_new_image(d->mlx, width, height)))
		return (-1);
	if (mlx_image_to_window(d->mlx, d->cam.img, 0, 0) == -1)
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
	if (set_mmap_mlx(d, d->c) == -1)
		return (terminate_cub_ui(d, &d->mmap, 1));
	return (0);
}
