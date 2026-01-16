/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:00:16 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/16 18:16:54 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	terminate_cub(data_t *d, mmap_t *mmap, int err);
int	exit_err(void);

int	exit_err(void)
{
	printf("%s\n", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

/* img->window->mlx */
/* 2 elements: mmap and camera */
int	terminate_cub(data_t *d, mmap_t *mmap, int err)
{
	if (NULL != mmap->img)
	{
		mlx_delete_image(d->mlx, mmap->img);
		mmap->img = NULL;
	}
	if (NULL != d->cam.img)
	{
		mlx_close_window(d->mlx);
		d->cam.img = NULL;
	}
	if (NULL != d->mlx)
		mlx_close_window(d->mlx);
	mlx_terminate(d->mlx);
	d->mlx = NULL;
	if (err == 1)
		return(-1);
	return (0);
}
