/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:48:11 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/11 19:48:35 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cam_bg(t_data *d);

void	cam_bg(t_data *d)
{
	t_ipair	i;
	t_color	ref;
	uint32_t color;

	i.y = 0;
	ref = d->config.textures.ceiling;
	color = color_px(ref.r, ref.g, ref.b, 120);
	while (i.y < (int)d->cam.img->height)
	{
		if (i.y == (int)d->cam.img->height / 2)
		{
			ref = d->config.textures.floor;
			color = color_px(ref.r, ref.g, ref.b, 255);
		}
		i.x = 0;
		while (i.x < (int)d->cam.img->width)
		{
			mlx_put_pixel(d->cam.img, i.x, i.y, color);
			i.x++;
		}
		i.y++;
	}
}
