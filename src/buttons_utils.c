/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:14:05 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/17 21:17:45 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"

void	player_mov(data_t *data, player_t *player)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		player->angle -= 0.05;
		if (player->angle < 0)
			player->angle += 2 * PI;
		player->dp.x = cos(player->angle);
		player->dp.y = sin(player->angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		player->angle += 0.05;
		if (player->angle > 2 * PI)
			player->angle -= 2 * PI;
		player->dp.x = cos(player->angle);
		player->dp.y = sin(player->angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		player->p.x -= player->dp.x;
		player->p.y -= player->dp.y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		player->p.x += player->dp.x;
		player->p.y += player->dp.y;
	}
}

void	key_hooks(void *param)
{
	data_t	*data;
	
	data = (data_t *)param;
	
	player_mov(data, &data->player);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ENTER))
	{
		mlx_delete_image(data->mlx, data->debug);
		data->debug = NULL;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}
