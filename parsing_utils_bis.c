/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:54:52 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/18 18:45:30 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	if (i != 3)
		return (false);
	else
		return (true);
}

bool	check_validity(t_data *data)
{
	if (data->sprites.img_north.img == NULL || data->sprites.img_south.img == NULL ||
	data->sprites.img_west.img == NULL || data->sprites.img_east.img == NULL)
		return (false);
	else
		return (true);
}

bool	check_commas(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		return (ft_printf("Error\nInvalid color format\n"), false);
	else
		return (true);
}

bool	check_newline(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			if (str[i] && str[i] == '\n')
			{
				while (str[i])
				{
					if (str[i] != '\n')
						return (false);
					i++;
				}
			}	
		}
		i++;
	}
	return (true);
}
