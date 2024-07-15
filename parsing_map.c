/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:09:06 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/15 18:35:12 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_characters(char **map)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (map[j])
	{
		dprintf(2, "boucle parse_map j\n");
		while (ft_strchr("01NSWE ", map[j][i]))
		{
			dprintf(2, "boucle parse_map i\n");
			i++;
		}

		if (map[j][i] != '\n')
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
	int	i;
	int	j;
	
	data->tc = 2;
	i = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			dprintf(2, "%c", map[j][i]);
			i++;
		}
		j++;
	}
	if (!check_characters(map))
		return (false);
	return (true);
}