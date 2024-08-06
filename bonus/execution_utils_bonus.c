/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:21:30 by dvalino-          #+#    #+#             */
/*   Updated: 2024/08/06 19:29:45 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

// 1 for max otherwise min
int	max_min(int option, int a, int b)
{
	if (option == 1)
	{
		if (a > b)
			return (a);
		return (b);
	}
	else
	{
		if (a < b)
			return (a);
		return (b);
	}
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
	if (x < 0 || x > WIN_WIDTH)
		return (0);
	if (y < 0 || y > WIN_WIDTH)
		return (0);
	return (1);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	found_player_pos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->mini_map.map[i])
	{
		j = 0;
		while (data->mini_map.map[i][j])
		{
			if (is_player(data->mini_map.map[i][j]))
			{
				data->player_char = data->mini_map.map[i][j];
				data->mini_map.p_pos.x = i;
				data->mini_map.p_pos.y = j;
				data->player.pos_x = i + 0.5;
				data->player.pos_y = j + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}
