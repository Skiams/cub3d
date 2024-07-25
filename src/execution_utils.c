/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:21:30 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/25 15:21:35 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	return (r << 16 | g << 8 | b);
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	acceptable_coordinates(int x, int y)
{
	if (x < 0 || x > WINDOW_WIDTH)
		return (0);
	if (y < 0 || y > WINDOW_WIDTH)
		return (0);
	return (1);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

