/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 23:06:23 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/09 17:16:53 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calculate_line_mmap(t_cam *cam, t_player *p, t_line *line, t_const c)
{
	line->start.x = (p->p.x + p->dp.x * p->rad_size) * c.mmap_scale;
	line->start.y = (p->p.y + p->dp.y * p->rad_size) * c.mmap_scale;
	line->end.x = (p->p.x + p->dp.x * -cam->sun.ray_len) * c.mmap_scale;
	line->end.y = (p->p.y + p->dp.y * -cam->sun.ray_len) * c.mmap_scale;
	line->delta.x = -(line->end.x - line->start.x);
	line->delta.y = -(line->end.y - line->start.y);
	line->draw.steps = util_get_max(line->delta.x, line->delta.y);
	line->draw.thick.x = -p->dp.y;
	line->draw.thick.y = p->dp.x;
	line->draw.color = color_px(209, 107, 165, 255);
}

void	draw_line_mmap(mlx_image_t *img, t_fpair start, t_fpair d, t_draw draw)
{
	t_fpair	pos;
	t_fpair	inc;
	int		i;
	int		w;

	w = -2;
	while (++w <= 1)
	{
		pos.x = start.x + draw.thick.x * (float) w;
		pos.y = start.y + draw.thick.y * (float) w;
		inc.x = d.x / draw.steps;
		inc.y = d.y / draw.steps;
		i = draw.steps;
		while (i--)
		{
			if (pos.x >= 0&& pos.x < img->width && \
				pos.y >= 0 && pos.y < img->height)
				mlx_put_pixel(img, pos.x, pos.y, draw.color);
			pos.x += inc.x;
			pos.y += inc.y;
		}
	}
}

void	paint_mmap_grid(t_mmap *mmap, t_const *c, t_map *map)
{
	t_ipair		i;
	int32_t		color;

	i.y = 0;
	while (i.y < map->height)
	{
		i.x = 0;
		while (i.x < map->width)
		{
			color = set_color_mmap(map->grid[i.y][i.x]);
			paint_pixel_mmap(mmap, c, i, color);
			i.x++;
		}
		i.y++;
	}
}

static void	set_start(t_player *pl, t_const *c)
{
	int	i;

	i = 0;
	while (i++ < c->fov / 4)
	{
		pl->angle -= 0.02;
		if (pl->angle < 0)
			pl->angle += 2 * PI;
	}
	pl->dp.x = cos(pl->angle);
	pl->dp.y = sin(pl->angle);
}

void	draw_rays_mmap(t_cam *cam, t_mmap *mmap, t_const *c, t_map *map)
{
	t_player	*pl;
	float		tmp;
	int			i;

	pl = mmap->player;
	tmp = mmap->player->angle;
	set_start(pl, c);
	i = 0;
	while (i < c->fov)
	{
		set_ray(&cam->sun, pl, *c);
		ray_loop(&cam->sun, map);
		calculate_line_mmap(cam, pl, &mmap->line, *c);
		draw_line_mmap(mmap->img, mmap->line.start, \
				 mmap->line.delta, mmap->line.draw);
		pl->angle += 0.02;
		if (pl->angle > 2 * PI)
			pl->angle -= 2 * PI;
		pl->dp.x = cos(pl->angle);
		pl->dp.y = sin(pl->angle);
		i += 2;
	}
	pl->angle = tmp;
	pl->dp.x = cos(pl->angle);
	pl->dp.y = sin(pl->angle);
}

void	render_mmap(t_cam *cam, t_mmap *mmap, t_const *c, t_map *map)
{
	paint_mmap_grid(mmap, c, map);
	draw_player(mmap, mmap->in_pos, c->pl_radius);
	draw_rays_mmap(cam, mmap, c, map);
}
