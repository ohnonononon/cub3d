/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:45:40 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/19 00:00:52 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void debug_player_line(char *buf, size_t bufsize,
					   float player_x, float player_y, float player_angle,
					   float line_end_x, float line_end_y)
{
	snprintf(buf, bufsize,
		  "Player: (%.2f, %.2f), Angle: %.2f rad"
		  "Line end: (%.2f, %.2f)",
		  player_x, player_y, player_angle,
		  line_end_x, line_end_y
		  );
}

void	print_dbg(data_t *d)
{
	char	bfr[264];
	ipair_t	i;

	i.y = (d->c.height / 5) ;
	i.x = (d->c.width / 12) * 2;
	if (d->debug != NULL)
		mlx_delete_image(d->mlx, d->debug);
	debug_player_line(bfr, 264, d->player.p.x, d->player.p.y, \
				   d->player.angle, \
				   d->line.end.x, d->line.end.y);
	d->debug = mlx_put_string(d->mlx, bfr, i.x, i.y);
	mlx_image_to_window(d->mlx, d->debug, 0, 0);
}

