/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:09:06 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/25 20:55:24 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static bool	check_north_south(char **map, int pos_y, int pos_x, int code)
{
	if (code == SOUTH)
	{
		while (map[pos_y][pos_x])
		{
			if (map[pos_y][pos_x] == '1')
				return (true);
			pos_y++;
		}
	}
	if (code == NORTH)
	{
		while (map[pos_y][pos_x])
		{
			if (map[pos_y][pos_x] == '1')
				return (true);
			pos_y--;
		}
	}
	return (false);
}

static bool	check_east_west(char **map, int pos_y, int pos_x, int code)
{
	if (code == WEST)
	{
		while (map[pos_y][pos_x])
		{
			if (map[pos_y][pos_x] == '1')
				return (true);
			pos_x--;
		}
	}
	if (code == EAST)
	{
		while (map[pos_y][pos_x])
		{
			if (map[pos_y][pos_x] == '1')
				return (true);
			pos_x++;
		}
	}
	return (false);
}

bool	check_side(char **map, int *j, int *i)
{
	int	pos_x;
	int	pos_y;

	pos_x = *i;
	pos_y = *j;
	if (!check_north_south(map, pos_y, pos_x, SOUTH))
		return (false);
	if (!check_north_south(map, pos_y, pos_x, NORTH))
		return (false);
	if (!check_east_west(map, pos_y, pos_x, WEST))
		return (false);
	if (!check_east_west(map, pos_y, pos_x, EAST))
		return (false);
	return (true);
}

static bool	check_characters(t_data *data, char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i] && ft_strchr("01NSWE ", map[j][i]))
		{
			if (map[j][i] && ft_strchr("NSWE", map[j][i]) && data->p_nb == 0)
			{
				data->p_pos_x = i;
				data->p_pos_y = j;
				data->p_nb = 1;
			}
			else if (map[j][i] && ft_strchr("NSWE", map[j][i])
				&& data->p_nb != 0)
				return (ft_printf("Error\nOnly one player allowed\n"), false);
			i++;
		}
		if (map[j][i] && map[j][i] != '\n')
			return (ft_printf("Error\nWrong map characters\n"), false);
		j++;
	}
	return (true);
}

bool	parse_map(t_data *data, char **map)
{
	if (!check_characters(data, map))
		return (false);
	if (!check_edges(map))
		return (false);
	return (true);
}
