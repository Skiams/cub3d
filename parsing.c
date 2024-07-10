/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:20 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/10 14:37:41 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



bool	parsing(char *argv, t_data *data)
{
	if (check_format(argv) == false || is_path_dir(argv) == true)
		return (ft_printf("Error\nInvalid map format\n", false));
	data->map_line = mini_gnl(open(argv, O_RDONLY));
	printf("map_line1 = %s\n", data->map_line);
	if (!data->map_line)
		return (ft_printf("Error\nCan't read the map\n", false));
	
	return (true);
}
