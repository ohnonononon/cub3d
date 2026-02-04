/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:00:16 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/16 18:57:05 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

int	exit_err(void);
int	terminate_cub_ui(data_t *d, mmap_t *mmap, int err);
int	terminate_cub_data(data_t *d, int err);
int	terminate_cub(data_t *d, int err);

int	exit_err(void)
{
	printf("%s\n", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

/* img->window->mlx */
/* 2 elements: mmap and camera */
int	terminate_cub_ui(data_t *d, mmap_t *mmap, int err)
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

int	terminate_cub_data(data_t *d, int err)
{
	if (d->mapdata.map != NULL)
	{
		free(d->mapdata.map);
		d->mapdata.map = NULL;
	}
	if (err == 1)
		return (-1);
	return (0);
}

int	terminate_cub(data_t *d, int err)
{
	err += terminate_cub_data(d, err);
	err += terminate_cub_ui(d, &d->mmap, err);
	if (err < 0)
		return (exit_err());
	return (EXIT_SUCCESS);
}
