/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:09:06 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/16 22:03:31 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_characters(char **map)
{
	int	i;
	int	j;
	

	j = 0;
	while (map[j])
	{
		i = 0;
		dprintf(2, "boucle parse_map j\n");
		while (map[j][i] && ft_strchr("01NSWE ", map[j][i]))
		{
			dprintf(2, "boucle parse_map i\n");
			i++;
		}
		if (map[j][i] && map[j][i] != '\n')
		{
			dprintf(2, "map[j][i] = %c\n", map[j][i]);
			return (ft_printf("Error\nWrong map characters\n"), false);		
		}
		j++;
	}
	return (true);
}

bool parse_map(t_data *data, char **map)
{
	
	data->tc = 2;
	if (!check_characters(map))
		return (false);
	return (true);
}