/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:36:46 by ohnonon           #+#    #+#             */
/*   Updated: 2026/01/17 18:37:09 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int util_roundf(float x)
{
    if (x >= 0.0f)
        return ((int)(x + 0.5f));
    else
        return ((int)(x - 0.5f));
}

int	util_get_max(float a, float b)
{
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	if (a < b)
		return (util_roundf(b));
	return (util_roundf(a));
}
