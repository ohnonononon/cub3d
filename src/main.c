/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/02/10 18:04:35 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include "parser.h"

void	cam_bg(t_data *d)
{
	t_ipair	i;
	uint32_t color;

	i.y = 0;
	color = color_px(d->config.textures.ceiling.r,
				  d->config.textures.ceiling.g,
				  d->config.textures.ceiling.b, 255);
	while (i.y < (int)d->cam.img->height)
	{
		if (i.y == (int)d->cam.img->height / 2)
			color = color_px(d->config.textures.floor.r,
					d->config.textures.floor.g,
					d->config.textures.floor.b, 255);
		i.x = 0;
		while (i.x < (int)d->cam.img->width)
		{
			mlx_put_pixel(d->cam.img, i.x, i.y, color);
			i.x++;
		}
		i.y++;
	}
}

// new len for normalised ray len
/* NOTE:
*  Size of rays is of d->c.width
*/
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
	if (rd[i].side == 0)
		t->wall_x = pl->p.y + rd[i].len * sin(rd[i].angle);
	else
		t->wall_x = pl->p.x + rd[i].len * cos(rd[i].angle);
	t->wall_x -= floorf(t->wall_x);
	t->side = rd[i].side;
	if (t->side == '0')
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

	tex = &ass->xpm[t->orient]->texture;
	step = tex->height / v->wall_h;
	tex_pos = 0.0f;
	t->tex_x = t->wall_x * tex->width;
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
			t->tex_y = tex->height - 1;
		t->color = get_tex_pixel(tex, t->tex_x, t->tex_y);
		mlx_put_pixel(d->img, v->i, y, t->color);
		y++;
		tex_pos += step;
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
		rays[v.i].angle = start_angle + (v.i * angle_i);
		// while (rays[v.i].angle < 0)
		// 	rays[v.i].angle += 2 * PI;
		// while (rays[v.i].angle > 2 * PI)
		// 	rays[v.i].angle -= 2 * PI;
		set_cam_ray(d, &rays[v.i]);
		set_vline(d, &v, rays[v.i].len);
		set_tex(&d->t, rays, &d->player, v.i);
		// draw_vline(&d->ass, &d->cam, &v, &d->t);
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

	d.d_flag = 0;
	if (set_data(&d) == -1)
		return (EXIT_FAILURE);
	mlx_loop_hook(d.mlx, &program_loop, &d);
	mlx_loop(d.mlx);
	return (terminate_cub(&d, 0));
}
