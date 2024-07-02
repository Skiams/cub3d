/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:20 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/02 19:00:37 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_format(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'b')
		return (ft_printf("Error\nWrong map format\n"), exit(1));
	if (str[i - 2] != 'u')
		return (ft_printf("Error\nWrong map format\n"), exit(1));
	if (str[i - 3] != 'c')
		return (ft_printf("Error\nWrong map format\n"), exit(1));
	if (str[i - 4] != '.')
		return (ft_printf("Error\nWrong map format\n"), exit(1));
}

// bool	parsing()
// {
	
// }
