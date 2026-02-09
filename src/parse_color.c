/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olreshet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by olreshet          #+#    #+#             */
/*   Updated: 2026/02/08 19:04:46 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static void free_components(char **components)
{
	int i;

	i = 0;
	while (components[i])
	{
		free(components[i]);
		i++;
	}
	free(components);
}

int is_valid_number(const char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int validate_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

static int parse_rgb_components(char **comp, int *r, int *g, int *b)
{
	if (!is_valid_number(comp[0]) || !is_valid_number(comp[1]) || !is_valid_number(comp[2]))
		return (0);
	*r = ft_atoi(comp[0]);
	*g = ft_atoi(comp[1]);
	*b = ft_atoi(comp[2]);
	return (1);
}

int parse_color(char *color_str, t_color *color)
{
	char **components;
	int r;
	int g;
	int b;

	components = ft_split(color_str, ',');
	if (!components || !components[0] || !components[1] || !components[2] || components[3])
	{
		if (components)
			free_components(components);
		return (0);
	}
	if (!parse_rgb_components(components, &r, &g, &b))
	{
		free_components(components);
		return (0);
	}
	free_components(components);
	if (!validate_rgb_values(r, g, b))
		return (0);
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}
