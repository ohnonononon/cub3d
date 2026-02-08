/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throttle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:41:21 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/20 19:45:26 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <sys/time.h>

static double	get_time_ms(void)
{
    struct timeval	tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

int	throttle_fps()
{
	static double	last_frame = 0;
	double			now;
	double			dt;

	now = get_time_ms();
	dt = now - last_frame;
	if (dt < 1000.0/60.0)
		return (-1);
	last_frame = now;
	return (0);
}
