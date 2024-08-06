/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:09:06 by ahayon            #+#    #+#             */
/*   Updated: 2024/08/06 19:28:35 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

static bool	check_north_south(char **map, int pos_y, int pos_x, int code)
{
	int	i;

	i = get_last_line(map);
	if (code == SOUTH)
	{
		while (pos_y < i && map[pos_y][pos_x]
			&& ft_strchr("NSWE01D", map[pos_y][pos_x]))
		{
			if (map[pos_y][pos_x] == '1')
				return (true);
			pos_y++;
		}
	}
	if (code == NORTH)
	{
		while (pos_y >= 0 && map[pos_y][pos_x]
			&& ft_strchr("NSWE01D", map[pos_y][pos_x]))
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
		while (map[pos_y][pos_x] && ft_strchr("NSWE01D", map[pos_y][pos_x]))
		{
			if (map[pos_y][pos_x] == '1')
				return (true);
			pos_x--;
		}
	}
	if (code == EAST)
	{
		while (map[pos_y][pos_x] && ft_strchr("NSWE01D", map[pos_y][pos_x]))
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
		while (map[j][i] && ft_strchr("01NSWED ", map[j][i]))
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
	if (data->p_nb != 1)
		return (ft_printf("Error\nWrong map parameters\n"), false);
	if (!check_edges(map))
		return (false);
	return (true);
}
