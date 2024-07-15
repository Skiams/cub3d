/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:49:43 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/15 14:18:35 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	static t_data	data = {0};
	
	if (data.img_north == NULL)
		dprintf(2, "it is null\n");
	int height = 200;
	int width = 200;
	if (argc != 2)
		ft_printf("Error: Wrong argument\nPlease enter one .cub file as argument");
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.img_height = &height;
	data.img_width = &width;
	if (!parsing(argv[1], &data))
		return (printf("problem parsing"), 1);
	return (0);
}