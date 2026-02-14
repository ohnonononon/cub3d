/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 02:50:04 by ohnonon           #+#    #+#             */
/*   Updated: 2026/02/14 03:20:29 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_cam_ray(t_data *d, t_raydata *r)
{
	float	angletmp;

	angletmp = d->player.angle;
	d->player.angle = r->angle;
	set_ray(&r->ray, &d->player, d->c);
	ray_loop(&r->ray, &d->config.map);
	r->len = r->ray.ray_len * cosf(angletmp - r->angle);
	if (r->len < 0.00001f)
		r->len = 0.00001f;
	d->player.angle = angletmp;
}

void	set_vline(t_data *d, t_vline *v, float len)
{
	v->wall_h = (d->c.tile_size / len) * d->c.proj_plane_dist;
	v->start_y = (int)(((float)d->c.height / 2) - (v->wall_h / 2));
	v->end_y = (int)(((float)d->c.height / 2) + (v->wall_h / 2));
}

void	draw_vline(t_assets *ass, t_cam *d, t_vline *v, t_tex_tools *t)
{
	mlx_texture_t	*tex;
	int				y;
	int				draw_start;
	int				draw_end;

	tex = ass->tex[t->orient];
	draw_start = v->start_y;
	draw_end = v->end_y;
	if (v->start_y < 0)
		draw_start = 0;
	if (draw_end >= (int)d->img->height)
		draw_end = d->img->height - 1;
	y = draw_start;
	while (y <= draw_end)
	{
		t->tex_y = (tex->height * (y - v->start_y)) / v->wall_h;
		if (t->tex_y >= (int)tex->height)
			t->tex_y = tex->height - 1;
		if (t->tex_y < 0)
			t->tex_y = 0;
		t->color = get_tex_pixel(tex, t->tex_x, t->tex_y);
		mlx_put_pixel(d->img, v->i, y, t->color);
		y++;
	}
}

void	render_cam(t_data *d)
{
	t_vline		v;
	float		angle_i;
	float		start_angle;

	cam_bg(d);
	angle_i = d->c.fov / (float)d->c.width;
	start_angle = d->player.angle - (d->c.fov / 2.0);
	while (start_angle < 0)
		start_angle += 2 * PI;
	while (start_angle >= 2 * PI)
		start_angle -= 2 * PI;
	v.i = 0;
	while (v.i < d->c.width)
	{
		d->rays[v.i].angle = normalize_angle(start_angle, v.i, angle_i);
		set_cam_ray(d, &d->rays[v.i]);
		set_vline(d, &v, d->rays[v.i].len);
		set_tex(&d->ass, &d->t, &d->rays[v.i], &d->player);
		draw_vline(&d->ass, &d->cam, &v, &d->t);
		v.i++;
	}
}
