/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:57:32 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/25 15:57:34 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	change_player_pos(t_data *data)
{
	data->mini_map.map[data->mini_map.p_pos.x][data->mini_map.p_pos.y] = '0';
	data->mini_map.p_pos.x = (int)data->player.pos_x;
	data->mini_map.p_pos.y = (int)data->player.pos_y;
	if (data->mini_map.player_pixel.x < 0)
	{
		data->mini_map.p_pos.x -= 1;
		data->mini_map.player_pixel.x = data->mini_map.block_h - 1;
	}
	else if (data->mini_map.player_pixel.x >= data->mini_map.block_h)
	{
		data->mini_map.p_pos.x += 1;
		data->mini_map.player_pixel.x = 0;
	}
	if (data->mini_map.player_pixel.y < 0)
	{
		data->mini_map.p_pos.y -= 1;
		data->mini_map.player_pixel.y = data->mini_map.block_w - 1;
	}
	else if (data->mini_map.player_pixel.y >= data->mini_map.block_w)
	{
		data->mini_map.p_pos.y += 1;
		data->mini_map.player_pixel.y = 0;
	}
	data->mini_map.map[data->mini_map.p_pos.x][data->mini_map.p_pos.y]
		= data->player_char;
}

static void	calculate_start_and_end(t_mini_map *mini_map)
{
	mini_map->nbr_columns = ft_strlen(mini_map->map[mini_map->p_pos.x]);
	mini_map->start.x = max_min(1, 0, mini_map->p_pos.x - ZOOM_MINI / 2);
	mini_map->start.y = max_min(1, 0, mini_map->p_pos.y - ZOOM_MINI / 2);
	mini_map->end.x = max_min(0, mini_map->nbr_lines,
			mini_map->p_pos.x + ZOOM_MINI / 2);
	mini_map->end.y = max_min(0, mini_map->nbr_columns,
			mini_map->p_pos.y + ZOOM_MINI / 2);
}

void	calculate_map_arg(t_mini_map *mini_map)
{
	int	new_player_x;
	int	new_player_y;

	calculate_start_and_end(mini_map);
	new_player_x = mini_map->p_pos.x
		+ mini_map->player_pixel.x / mini_map->block_h;
	new_player_y = mini_map->p_pos.y
		+ mini_map->player_pixel.y / mini_map->block_w;
	if (new_player_x != mini_map->p_pos.x
		|| new_player_y != mini_map->p_pos.y)
	{
		mini_map->p_pos.x = new_player_x;
		mini_map->p_pos.y = new_player_y;
		mini_map->player_pixel.x
			= mini_map->player_pixel.x % mini_map->block_h;
		mini_map->player_pixel.y
			= mini_map->player_pixel.y % mini_map->block_w;
	}
	mini_map->playerScreen.x
		= (mini_map->p_pos.x - mini_map->start.x)
		* mini_map->block_h + mini_map->player_pixel.x;
	mini_map->playerScreen.y
		= (mini_map->p_pos.y - mini_map->start.y)
		* mini_map->block_w + mini_map->player_pixel.y;
}

void	draw_player(t_data *data)
{
	int		i;
	int		j;
	int		player_h;
	int		player_w;
	t_point	b;

	player_w = 5;
	player_h = 5;
	i = -1;
	while (++i < player_h)
	{
		j = -1;
		while (++j < player_w)
		{
			if (acceptable_coordinates(i + data->mini_map.playerScreen.x - 2,
					j + data->mini_map.playerScreen.y - 2))
				my_mlx_pixel_put(&data->img,
					j + data->mini_map.playerScreen.y - 2,
					i + data->mini_map.playerScreen.x - 2, 0x00000000);
		}
	}
	b.x = data->mini_map.playerScreen.x + data->player.dir_x * 5;
	b.y = data->mini_map.playerScreen.y + data->player.dir_y * 5;
	draw_line(data->mini_map.playerScreen, b, data);
}

void	draw_map(t_data *data)
{
	int		i;
	int		j;
	int		len;
	t_point	point;

	i = data->mini_map.start.x;
	while (data->mini_map.map[i] && i < data->mini_map.end.x)
	{
		len = ft_strlen(data->mini_map.map[i]);
		j = data->mini_map.start.y - 1;
		while (++j < len && j < data->mini_map.end.y)
		{
			point.x = (i - data->mini_map.start.x) * data->mini_map.block_h;
			point.y = (j - data->mini_map.start.y) * data->mini_map.block_w;
			if (j < len && data->mini_map.map[i][j] == '1')
				draw_square(point.x, point.y, 0x00CC0000 / 2, data);
			else if (data->mini_map.map[i][j] && (data->mini_map.map[i][j]
				== '0' || is_player(data->mini_map.map[i][j])))
				draw_square(point.x, point.y, 0x00FF9933, data);
		}
		i++;
	}
	draw_player(data);
}
