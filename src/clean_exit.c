/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:00:16 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/08 22:12:37 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

int	exit_err(void);
int	terminate_cub_ui(t_data *d, t_mmap *mmap, int err);
int	terminate_cub_data(t_data *d, int err);
int	terminate_cub(t_data *d, int err);

int	exit_err(void)
{
	printf("%s\n", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

/* img->window->mlx */
/* 2 elements: mmap and camera */
int	terminate_cub_ui(t_data *d, t_mmap *mmap, int err)
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

int	terminate_cub_data(t_data *d, int err)
{
	int	i;

	i = 0;
	if (d->config.map.grid != NULL)
	{
		while (d->config.map.grid[i] != NULL)
			free(d->config.map.grid[i++]);
		free(d->config.map.grid);
		d->config.map.grid = NULL;
	}
	if (err == 1)
		return (-1);
	return (0);
}

int	terminate_cub(t_data *d, int err)
{
	err += terminate_cub_data(d, err);
	err += terminate_cub_ui(d, &d->mmap, err);
	if (err < 0)
		return (exit_err());
	return (EXIT_SUCCESS);
}
