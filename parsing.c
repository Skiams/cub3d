/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:20 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/16 22:02:55 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	assign_texture(t_data *data, char *path, int code)
{
	if (code == NORTH)
	{
		data->img_north = mlx_xpm_file_to_image(data->mlx, path, data->img_height, data->img_width);
		if (data->img_north == NULL)
			return (false);
	}
	else if (code == SOUTH)
	{
		data->img_south = mlx_xpm_file_to_image(data->mlx, path, data->img_height, data->img_width);
		if (data->img_south == NULL)
			return (false);
	}
	else if (code == EAST)
	{
		data->img_east = mlx_xpm_file_to_image(data->mlx, path, data->img_height, data->img_width);
		if (data->img_east == NULL)
			return (false);
	}
	else if (code == WEST)
	{
		data->img_west = mlx_xpm_file_to_image(data->mlx, path, data->img_height, data->img_width);
		if (data->img_west == NULL)
			return (false);
	}
	return (true);
}

static bool get_colors(t_data *data, char *map_line, int **i, int code)
{
	int		j;
	char	*colors;
	char	**colors_tab;
	
	(**i) += 2;
	j = (**i);
	while (map_line[**i] && map_line[**i] != '\n')
		(**i)++;
	colors = ft_substr(map_line, j, ((**i) - j));
	if (!check_commas(colors))
		return (false);
	colors_tab = ft_split(colors, ',');
	free(colors);
	if (!check_tab(colors_tab))
		return (ft_printf("Error\nInvalid colors\n"), false);
	j = 0;
	while (colors_tab[j])
	{
		if (code == FLOOR)
		{
			data->f_colors[j] = ft_atoi_cub(colors_tab[j]);
			if (data->f_colors[j] < 0 || data->f_colors[j] > 255)
				return (ft_printf("Error\nInvalid colors\n"), false);
		}
		else if (code == CEILING)
		{
			data->c_colors[j] = ft_atoi_cub(colors_tab[j]);
			if (data->c_colors[j] < 0 || data->c_colors[j] > 255)
				return (ft_printf("Error\nInvalid colors\n"), false);
		}
		j++;
	}
	dprintf(2, "boucle get_colors et map_line[i] = %i\n", map_line[**i]);
	return (true);
}

static bool	get_texture(t_data *data, char *map_line, int **i, int code)
{
	char	*texture;
	int		j;
	
	(**i) += 2;
	if (map_line[**i] && (map_line[**i] != 32 && map_line[**i] != 9))
		return (ft_printf("Error\nInvalid texture format\n"), false);
	while (map_line[**i] && (map_line[**i] == 32 || map_line[**i] == 9 || map_line[**i] == '\n')) 
		(**i)++;
	j = (**i);
	while (map_line[**i] && (map_line[**i] != 32 && map_line[**i] != 9 && map_line[**i] != '\n'))
		(**i)++;
	printf("i = %d, j = %d\n", (**i), j);
	texture = ft_substr(map_line, j, ((**i) - j));
	if (!texture)
		return (ft_printf("Error\nMemory allocation problem\n"), false);
	printf("texture = %s\n", texture);
	if (is_path_dir(texture) || !check_format(texture, 2))
		return (false);
	if (!assign_texture(data, texture, code))
		return (false);
	free(texture);
	return (true);
}

static bool	check_param(t_data *data, char *map_line, int *i)
{
	while (map_line[*i])
	{
		while (map_line[*i] == 32 || map_line[*i] == 9 || map_line[*i] == '\n')
			(*i)++;
		if (map_line[*i] == 'N' && map_line[*i + 1] == 'O' &&
		(data->img_north != NULL || !get_texture(data, map_line, &i, NORTH)))
			return (ft_printf("Error\nWrong map parameters\n"), false);			
		else if (map_line[*i] == 'S' && map_line[*i + 1] == 'O' &&
		(data->img_south != NULL || !get_texture(data, map_line, &i, SOUTH)))
			return (ft_printf("Error\nWrong map parameters\n"), false);	
		else if (map_line[*i] == 'E' && map_line[*i + 1] == 'A' &&
		(data->img_east != NULL || !get_texture(data, map_line, &i, EAST)))
			return (ft_printf("Error\nWrong map parameters\n"), false);	
		else if (map_line[*i] == 'W' && map_line[*i + 1] == 'E' &&
		(data->img_west != NULL || !get_texture(data, map_line, &i, WEST)))
			return (ft_printf("Error\nWrong map parameters\n"), false);	
		else if (map_line[*i] == 'F' && !get_colors(data, map_line, &i, FLOOR))
			return (false);
		else if (map_line[*i] == 'C' && !get_colors(data, map_line, &i, CEILING))
			return (false);
		else if (map_line[*i] != 32 && map_line[*i] != 9 && map_line[*i] != '\n' && map_line[*i] != '1')
		 	return (ft_printf("Error\nWrong map parameters\n"), false);
		else if (map_line[*i] == '1')
			break ;
		(*i)++;
	}
	if (!check_validity(data))
		return (false);
	return (true);
}

char	*get_map_only(char *map_line, int *i)
{
	int		j;
	char	*map_line_bis;
	
	j = (*i);
	while (map_line[*i])
		(*i)++;
	map_line_bis = ft_substr(map_line, j, (*i) - j);
	if (!map_line_bis)
		return (ft_printf("Error\nMalloc error\n"), NULL);
	return (map_line_bis);
}

bool	parsing(char *argv, t_data *data)
{
	int		i;

	i = 0;
	if (!check_format(argv, 1) || is_path_dir(argv))
		return (ft_printf("Error\nInvalid map format\n", false));
	data->map_line = mini_gnl(open(argv, O_RDONLY));
	if (!data->map_line)
		return (ft_printf("Error\nCan't read the map\n", false));
	if (!check_param(data, data->map_line, &i))
		return (false);
	data->map_line_bis = get_map_only(data->map_line, &i);
	if (!data->map_line_bis)
		return (false);
	data->map = ft_split_cub(data->map_line_bis, '\n');
	// int j = 0;
	// while (data->map[j])
	// {
	// 	i = 0;
	// 	while (data->map[j][i])
	// 	{
	// 		dprintf(2, "%i", data->map[j][i]);
	// 		i++;
	// 	}
	// 	dprintf(2, "\n");
	// 	j++;
	// }
	if (!parse_map(data, data->map))
		return (ft_printf("Le parse map fail\n"), false);
	return (true);
}
