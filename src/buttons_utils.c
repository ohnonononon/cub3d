/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:14:05 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/14 15:21:32 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// IDEAS:
// 1. hacer el cambio, hacer retrieve tile y si esta en tile 1, hacer back
// 2. castear rayos y si colisiona y len < 1, no permitir mov en direccion

static void	player_rotate(t_data *data, t_player *player)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		player->angle -= 0.05;
		if (player->angle < 0)
			player->angle += 2 * PI;
		player->dp.x = cos(player->angle);
		player->dp.y = sin(player->angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		player->angle += 0.05;
		if (player->angle > 2 * PI)
			player->angle -= 2 * PI;
		player->dp.x = cos(player->angle);
		player->dp.y = sin(player->angle);
	}
}

static void	strafe_mov(t_data *data, t_player *player)
{
	t_fpair	side;

	side.x = -player->dp.y;
	side.y = player->dp.x;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (retrieve_tile(data->c, &data->config.map, player->p, side))
		{
			player->p.x -= side.x;
			player->p.y -= side.y;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (retrieve_tile(data->c, &data->config.map, player->p, side))
		{
			player->p.x += side.x;
			player->p.y += side.y;
		}
	}
}

static void	frontal_mov(t_data *data, t_player *player)
{
	t_fpair	tmp;

	tmp = player->p;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (retrieve_tile(data->c, &data->config.map, player->p, player->dp))
		{
			player->p.x += player->dp.x;
			player->p.y += player->dp.y;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (retrieve_tile(data->c, &data->config.map, player->p, player->dp))
		{
			player->p.x -= player->dp.x;
			player->p.y -= player->dp.y;
		}
	}
}

void	key_hooks(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	frontal_mov(data, &data->player);
	strafe_mov(data, &data->player);
	player_rotate(data, &data->player);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}
