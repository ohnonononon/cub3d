/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:14:05 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/17 16:17:09 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	buttons(mlx_key_data_t keydata, void *param);

static bool	is_button_pressed(mlx_key_data_t keydata)
{
	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
		return (true);
	return (false);
}

void	buttons(mlx_key_data_t keydata, void *param)
{
	data_t	*data;
	
	data = (data_t *)param;
	
	if (keydata.key == MLX_KEY_A && is_button_pressed(keydata))
		data->player.p.x -= 5;
	if (keydata.key == MLX_KEY_D && is_button_pressed(keydata))
		data->player.p.x += 5;
	if (keydata.key == MLX_KEY_S && is_button_pressed(keydata))
		data->player.p.y += 5;
	if (keydata.key == MLX_KEY_W && is_button_pressed(keydata))
		data->player.p.y -= 5;
}

