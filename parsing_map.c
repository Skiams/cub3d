/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:09:06 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/17 15:58:38 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if (map[j][i] && ft_strchr("NSWE", map[j][i]) && data->player_count == 0)
			{
				dprintf(2, "on est dans le check de joueur\n");
				data->p_pos_x = i;
				data->p_pos_y = j;
				data->player_count = 1;
				dprintf(2, "pos_x = %i\n", data->p_pos_x);
			}
			else if (map[j][i] && ft_strchr("NSWE", map[j][i]) && data->player_count != 0)
				return (ft_printf("Error\nOnly one player allowed\n"), false);
			i++;
		}
		if (map[j][i] && map[j][i] != '\n')
			return (ft_printf("Error\nWrong map characters\n"), false);
		j++;
	}
	return (true);
}

bool parse_map(t_data *data, char **map)
{
	if (!check_characters(data, map))
		return (false);
	return (true);
}
