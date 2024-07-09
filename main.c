/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:49:43 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/09 17:59:46 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	parsing(char *argv, t_data *data)
{
	check_format_cub(argv)
}

int	main(int argc, char **argv)
{
	static t_data	data = {0};
	
	if (argc != 2)
		ft_printf("Error: Wrong argument\nPlease enter a .cub file as argument");
	if (!parsing(argv[1]))
		return (1);
}