/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 02:29:01 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/14 03:49:26 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	get_tex_pixel(mlx_texture_t *tex, int x, int y);
void		set_tex(t_assets *ass, t_tex_tools *t, t_raydata *rd, \
			t_player *pl);

uint32_t	get_tex_pixel(mlx_texture_t *tex, int x, int y)
{
	int	i;

	i = (y * tex->width + x) * 4;
	return ((tex->pixels[i] << 24) | (tex->pixels[i + 1] << 16) | \
				(tex->pixels[i + 2] << 8) | 32);
}

void	set_tex(t_assets *ass, t_tex_tools *t, t_raydata *rd, t_player *pl)
{
	if (rd->ray.side == 0)
	{
		t->wall_x = pl->p.y + rd->ray.ray_len * rd->ray.ray.y;
		if (rd->ray.step.x > 0)
			t->orient = EAST;
		else
			t->orient = WEST;
	}
	else
	{
		t->wall_x = pl->p.x + rd->ray.ray_len * rd->ray.ray.x;
		if (rd->ray.step.y > 0)
			t->orient = SOUTH;
		else
			t->orient = NORTH;
	}
	t->wall_x = fmodf(t->wall_x, 64.0f) / 64.0f;
	t->tex_x = (int)(t->wall_x * ass->tex[t->orient]->width);
	if (rd->ray.side == 0 && rd->ray.ray.x > 0)
		t->tex_x = ass->tex[t->orient]->width - t->tex_x - 1;
	if (rd->ray.side == 1 && rd->ray.ray.y < 0)
		t->tex_x = ass->tex[t->orient]->width - t->tex_x - 1;
	if (t->tex_x < 0)
		t->tex_x = 0;
}
