/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:20 by ahayon            #+#    #+#             */
/*   Updated: 2024/08/05 20:31:00 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static bool	assign_colors(t_data *data, char **colors_tab, int j, int code)
{
	if (code == FLOOR)
	{
		data->sprites.floor[j] = ft_atoi_cub(colors_tab[j]);
		if (data->sprites.floor[j] < 0 || data->sprites.floor[j] > 255)
			return (ft_printf("Error\nInvalid colors\n"), false);
	}
	else if (code == CEILING)
	{
		data->sprites.ceiling[j] = ft_atoi_cub(colors_tab[j]);
		if (data->sprites.ceiling[j] < 0 || data->sprites.ceiling[j] > 255)
			return (ft_printf("Error\nInvalid colors\n"), false);
	}
	return (true);
}

static bool	get_colors(t_data *data, char *map_line, int **i, int code)
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
		return (free(colors), false);
	colors_tab = ft_split(colors, ',');
	free(colors);
	if (!check_tab(colors_tab))
		return (ft_printf("Error\nInvalid colors\n"), false);
	j = 0;
	while (colors_tab[j])
	{
		if (!assign_colors(data, colors_tab, j, code))
			return (free_tab(colors_tab), false);
		j++;
	}
	free_tab(colors_tab);
	return (true);
}

static bool	check_param(t_data *data, char *map_line, int *i)
{
	while (map_line[*i])
	{
		while (map_line[*i] == 32 || map_line[*i] == 9 || map_line[*i] == '\n')
			(*i)++;
		if (!texture_check(data, map_line, &i))
			return ((ft_printf("Error\nWrong map parameters\n"), false));
		else if (map_line[*i] == 'F' && !get_colors(data, map_line, &i, FLOOR))
			return (false);
		else if (map_line[*i] == 'C'
			&& !get_colors(data, map_line, &i, CEILING))
			return (false);
		else if (map_line[*i] != 32
			&& map_line[*i] != 9 && map_line[*i] != '\n' && map_line[*i] != '1')
			return (ft_printf("Error\nWrong map parameters\n"), false);
		else if (map_line[*i] == '1')
		{
			while (map_line[*i - 1] == 32)
				(*i)--;
			break ;
		}
		(*i)++;
	}
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
		return (free(map_line), ft_printf("Error\nMalloc error\n"), NULL);
	free(map_line);
	return (map_line_bis);
}

bool	parsing(char *argv, t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (ft_printf("Error\nMlx init failed\n"), false);
	if (!check_format(argv, 1) || is_path_dir(argv))
		return (ft_printf("Error\nInvalid map format\n"), false);
	data->fd = open(argv, O_RDONLY);
	if (data->fd == -1)
		return (ft_printf("Error\nCan't open the map\n"), false);
	data->map_line = mini_gnl(data->fd);
	if (!data->map_line)
		return (ft_printf("Error\nCan't read the map\n"), false);
	if (!check_param(data, data->map_line, &data->index))
		return (free(data->map_line), false);
	if (!check_validity(data))
		return (free(data->map_line),
			ft_printf("Error\nWrong map parameters\n"), false);
	data->map_line_bis = get_map_only(data->map_line, &data->index);
	if (!data->map_line_bis)
		return (false);
	if (!check_newline(data->map_line_bis))
		return (ft_printf("Error\nLinebreak in the map\n"), false);
	data->mini_map.map = ft_split_cub(data->map_line_bis, '\n');
	if (!parse_map(data, data->mini_map.map))
		return (false);
	return (true);
}
