/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:47:05 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/30 16:53:07 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

bool	assign_texture_bis(t_data *data, char *path, int code)
{
	if (code == EAST)
	{
		data->sprites.img_east.img = mlx_xpm_file_to_image(data->mlx_ptr,
				path, &(data->img_width), &(data->img_height));
		if (data->sprites.img_east.img == NULL)
			return (false);
	}
	else if (code == WEST)
	{
		data->sprites.img_west.img = mlx_xpm_file_to_image(data->mlx_ptr,
				path, &(data->img_width), &(data->img_height));
		if (data->sprites.img_west.img == NULL)
			return (false);
	}
	return (true);
}

bool	assign_texture(t_data *data, char *path, int code)
{
	if (code == NORTH)
	{
		data->sprites.img_north.img = mlx_xpm_file_to_image(data->mlx_ptr,
				path, &(data->img_width), &(data->img_height));
		if (data->sprites.img_north.img == NULL)
			return (false);
	}
	else if (code == SOUTH)
	{
		data->sprites.img_south.img = mlx_xpm_file_to_image(data->mlx_ptr,
				path, &(data->img_width), &(data->img_height));
		if (data->sprites.img_south.img == NULL)
			return (false);
	}
	else
	{
		if (!assign_texture_bis(data, path, code))
			return (false);
	}
	return (true);
}

bool	get_texture(t_data *data, char *map_line, int **i, int code)
{
	char	*texture;
	int		j;

	(**i) += 2;
	if (map_line[**i] && (map_line[**i] != 32 && map_line[**i] != 9))
		return (ft_printf("Error\nInvalid texture format\n"), false);
	while (map_line[**i] && (map_line[**i] == 32
			|| map_line[**i] == 9 || map_line[**i] == '\n'))
		(**i)++;
	j = (**i);
	while (map_line[**i] && (map_line[**i] != 32
			&& map_line[**i] != 9 && map_line[**i] != '\n'))
		(**i)++;
	texture = ft_substr(map_line, j, ((**i) - j));
	if (!texture)
		return (ft_printf("Error\nMemory allocation problem\n"), false);
	if (is_path_dir(texture) || !check_format(texture, 2))
		return (free(texture), false);
	if (!assign_texture(data, texture, code))
		return (free(texture), false);
	free(texture);
	return (true);
}

bool	texture_check(t_data *data, char *map, int **i)
{
	if (map[**i] == 'N' && map[**i + 1] == 'O'
		&& (data->sprites.img_north.img != NULL
			|| !get_texture(data, map, i, NORTH)))
		return (false);
	else if (map[**i] == 'S' && map[**i + 1] == 'O'
		&& (data->sprites.img_south.img != NULL
			|| !get_texture(data, map, i, SOUTH)))
		return (false);
	else if (map[**i] == 'E' && map[**i + 1] == 'A'
		&& (data->sprites.img_east.img != NULL
			|| !get_texture(data, map, i, EAST)))
		return (false);
	else if (map[**i] == 'W' && map[**i + 1] == 'E'
		&& (data->sprites.img_west.img != NULL
			|| !get_texture(data, map, i, WEST)))
		return (false);
	return (true);
}
