/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:45:07 by dvalino-          #+#    #+#             */
/*   Updated: 2024/08/02 17:49:43 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_door_total(char **map, t_data *data, int get_coord)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'D')
			{
				if (get_coord)
				{
					data->doors.coord_tab[i].x = x;
					data->doors.coord_tab[i].y = y;
					i++;
				}
				else
					data->doors.total++;
			}
			y++;
		}
		x++;
	}
}

int	open_door(int x, int y, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->doors.total)
	{
		if (data->doors.coord_tab[i].x == x
			&& data->doors.coord_tab[i].y == y)
			return (data->doors.is_open[i]);
	}
	return (1);
}

void	check_animation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->doors.total)
	{
		if (data->mini_map.p_pos.x == data->doors.coord_tab[i].x
			&& data->mini_map.p_pos.y == data->doors.coord_tab[i].y)
			data->is_in_door = 1;
		else if (data->is_in_door == 1
			&& (data->mini_map.p_pos.x != data->doors.coord_tab[i].x
			|| data->mini_map.p_pos.y != data->doors.coord_tab[i].y))
		{
			data->is_in_door = 0;
			data->anim_sprite.activate_animation = !data->anim_sprite.activate_animation;
		}
	}
}


void	draw_blackground(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT / 2)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			my_mlx_pixel_put(&data->img, j, i, 0x00000000);
			my_mlx_pixel_put(&data->img, j++, (WIN_HEIGHT / 2) + i,
				0x00000000);
		}
		i++;
	}
}
