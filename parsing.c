/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:20 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/10 18:29:57 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static bool	assign_texture(t_data *data, char *path, int code)
// {
// 	if (code == NORTH)
// 	{
// 		data->img_north = mlx_xpm_file_to_image(data->mlx, path, )
// 	}
		
// 	return (true);
// }

static bool	get_texture(t_data *data, char *map_line, int *i, int code)
{
	char	*texture;
	int		j;
	
	data->tc = 0;
	code = 0;
	(*i) += 2;
	if (map_line[*i] && (map_line[*i] != 32 && map_line[*i] != 9))
		return (ft_printf("Error\nInvalid "))
	while (map_line[*i] && (map_line[*i] == 32 || map_line[*i] == 9 || map_line[*i] == '\n')) 
		(*i)++;
	j = (*i);
	while (map_line[*i] && (map_line[*i] != 32 && map_line[*i] != 9 && map_line[*i] != '\n'))
		(*i)++;
	printf("i = %d, j = %d\n", (*i), j);
	texture = ft_substr(map_line, map_line[j], ((*i) - j));
	if (!texture)
		return (ft_printf("Error\nMemory allocation problem\n"), false);
	printf("texture = %s\n", texture);
	// if (!assign_texture(data, texture, code))
	// 	return (false);
	free(texture);
	return (true);
}
static bool	check_param(t_data *data, char *map_line)
{
	int	i;

	i = 0;
	while (map_line[i])
	{
		while (map_line[i] == 32 || map_line[i] == 9 || map_line[i] == '\n')
			i++;
		if (map_line[i] == 'N' && map_line[i + 1] == 'O' && (!get_texture(data, map_line, &i, NORTH)))
			return (false);			
		else if (map_line[i] == 'S' && map_line[i + 1] == 'O' && (!get_texture(data, map_line, &i, SOUTH)))
			return (false);
		else if (map_line[i] == 'W' && map_line[i + 1] == 'E' && (!get_texture(data, map_line, &i, WEST)))
			return (false);
		else if (map_line[i] == 'E' && map_line[i + 1] == 'A' && (!get_texture(data, map_line, &i, EAST)))
			return (false);
	}
	return (true);
}


bool	parsing(char *argv, t_data *data)
{
	if (check_format(argv, 1) == false || is_path_dir(argv) == true)
		return (ft_printf("Error\nInvalid map format\n", false));
	data->map_line = mini_gnl(open(argv, O_RDONLY));
	printf("map_line1 = %s\n", data->map_line);
	if (!data->map_line)
		return (ft_printf("Error\nCan't read the map\n", false));
	if (!check_param(data, data->map_line))
		return (false);
	return (true);
}
