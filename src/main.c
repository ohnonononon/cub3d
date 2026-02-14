/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:56:19 by nimatura          #+#    #+#             */
/*   Updated: 2026/02/14 02:51:31 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	program_loop(void *ptr)
{
	t_data			*d;

	d = (t_data *)ptr;

	key_hooks(d);
	calculate_main_ray(d);
	render_cam(d);
}

// char	*t1[3] = {"bin", "./maps/simple.cub" , NULL};
int	main(int argc, char **argv)
{
	t_data	d = {0};

	if (set_data(argc, argv, &d) == -1)
		return (EXIT_FAILURE);
	mlx_loop_hook(d.mlx, &program_loop, &d);
	mlx_loop(d.mlx);
	return (terminate_cub(&d, 0));
}
