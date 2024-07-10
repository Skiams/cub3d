/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:49:43 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/10 14:44:30 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	static t_data	data = {0};
	
	if (argc != 2)
		ft_printf("Error: Wrong argument\nPlease enter a .cub file as argument");
	if (!parsing(argv[1], &data))
		return (1);
	//printf("map_line = %s\n", data.map_line);
	return (0);
}