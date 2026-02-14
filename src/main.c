/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/02/14 02:13:57 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <unistd.h>

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

uint32_t	get_tex_pixel(mlx_texture_t *tex, int x, int y)
{
	int i;

	i = (y * tex->width + x) * 4;
	return (
	(tex->pixels[i] << 24) |
	(tex->pixels[i + 1] << 16) |
	(tex->pixels[i + 2] << 8) |
	(tex->pixels[i + 3])
);
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
		int	d_y = y - v->start_y;
		t->tex_y = (d_y * tex->height ) / v->wall_h;
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
	t_raydata	rays[d->c.width];
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
		rays[v.i].angle = normalize_angle(start_angle, v.i,  angle_i);
		set_cam_ray(d, &rays[v.i]);
		set_vline(d, &v, rays[v.i].len);
		set_tex(&d->ass, &d->t, &rays[v.i], &d->player);
		draw_vline(&d->ass, &d->cam, &v, &d->t);
		v.i++;
	}
}

void	program_loop(void *ptr)
{
	t_data			*d;

	d = (t_data *)ptr;

	if (throttle_fps() == -1)
		return ;
	key_hooks(d);
	calculate_main_ray(d);
	render_cam(d);
}

char	*t1[3] = {"bin", "./maps/simple.cub" , NULL};
int	main(void)
{
	int ac = 2;
	t_data	d = {0};
	if (set_data(ac, t1, &d) == -1)
		return (EXIT_FAILURE);
	mlx_loop_hook(d.mlx, &program_loop, &d);
	mlx_loop(d.mlx);
	return (terminate_cub(&d, 0));
}
