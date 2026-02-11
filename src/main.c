/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/02/11 20:05:21 by ohnonon          ###   ########.fr       */
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
    r->len = r->ray.ray_len * cosf(r->angle - angletmp);
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

void	set_tex(t_tex_tools *t, t_raydata *rd, t_player *pl, int i)
{
	t->wall_x = 0;
	if (rd[i].side == 0)
		t->wall_x = pl->p.y + rd[i].len * sinf(rd[i].angle);
	else
		t->wall_x = pl->p.x + rd[i].len * cosf(rd[i].angle);
	t->wall_x -= floorf(t->wall_x);
	t->side = rd[i].side;
	if (t->side == 0)
	{
		if (rd[i].angle < PI)
			t->orient = EAST;
		else
			t->orient = WEST;
	}
	else
	{
		if (rd[i].angle < PI)
			t->orient = SOUTH;
		else
			t->orient = NORTH;
	}
}

void	draw_vline(t_assets *ass, t_cam *d, t_vline *v, t_tex_tools *t)
{
	mlx_texture_t	*tex;
	float			tex_pos;
	float			step;
	int				y;

	(void)v;
	(void)d;
	(void)tex_pos;
	(void)step;
	(void)y;

	tex = ass->tex[t->orient];
	step = tex->height / v->wall_h;
	tex_pos = 0.0f;
	t->tex_x = ((int)t->wall_x * tex->width);
	if (t->tex_x < 0)
		t->tex_x = 0;
	if (v->start_y < 0)
		v->start_y = 0;
	if (v->end_y >= (int)d->img->height)
		v->end_y = d->img->height - 1;
	y = v->start_y;
	while (y <= v->end_y)
	{
		t->tex_y = (int)tex_pos;
		if (t->tex_y >= (int)tex->height)
		{
			t->tex_y = tex->height - 1;
		}
 		t->color = get_tex_pixel(tex, t->tex_x, t->tex_y);
 		mlx_put_pixel(d->img, v->i, y, t->color);
		tex_pos += step;
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
	start_angle = d->player.angle - d->c.fov / 2.0;
	while (start_angle < 0)
		start_angle += 2 * PI;
	while (start_angle >= 2 * PI)
		start_angle -= 2 * PI;
	v.i = 0;
	while (v.i < d->c.width)
	{
		rays[v.i].angle = normalize_angle(rays[v.i].angle, start_angle, v.i,  angle_i);
		set_cam_ray(d, &rays[v.i]);
		set_vline(d, &v, rays[v.i].len);
		set_tex(&d->t, rays, &d->player, v.i);
		draw_vline(&d->ass, &d->cam, &v, &d->t);
		v.i++;
	}
}

void	program_loop(void *ptr)
{
	t_data			*d;

	d = (t_data *)ptr;

	print_dbg(d);
	if (throttle_fps() == -1)
		return ;
	key_hooks(d);
	calculate_main_ray(d);
	render_cam(d);
	// upd_mmap_data(&d->mmap, d->c, &d->player);
	// render_mmap(&d->cam, &d->mmap, &d->c, &d->config.map);
}

// int	main(int ac, char **av)
int	main(void)
{
	t_data	d = {0};

	if (set_data(&d) == -1)
		return (EXIT_FAILURE);
	mlx_loop_hook(d.mlx, &program_loop, &d);
	mlx_loop(d.mlx);
	return (terminate_cub(&d, 0));
}
