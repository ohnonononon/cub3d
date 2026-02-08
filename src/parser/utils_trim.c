/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olreshet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by olreshet          #+#    #+#             */
/*   Updated: 2026/01/19 17:45:47 by olreshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void ft_copy_trimmed(char *trimmed, char *start, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		trimmed[i] = start[i];
		i++;
	}
	trimmed[len] = '\0';
}

char *ft_strtrim(char *s)
{
	char *start;
	char *end;
	char *trimmed;
	size_t len;

	if (!s)
		return (NULL);
	start = s;
	while (*start && ft_isspace(*start))
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = s + ft_strlen(s) - 1;
	while (end > start && ft_isspace(*end))
		end--;
	len = end - start + 1;
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_copy_trimmed(trimmed, start, len);
	return (trimmed);
}
