/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:13:38 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/25 16:13:47 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_player(t_data *data)
{
	double	move_speed;
	double	rot_speed;

	rot_speed = 0.008;
	move_speed = 0.02;
	player_rotation(data->game, &data->player, rot_speed);
	if (data->game.key_w)
		move_foward(data, move_speed);
	if (data->game.key_s)
		move_back(data, move_speed);
	if (data->player_char == 'W' || data->player_char == 'E')
		move_speed *= -1;
	if (data->game.key_a)
		move_left(data, move_speed);
	if (data->game.key_d)
		move_right(data, move_speed);
	change_player_pos(data);
	return (0);
}

void	set_player_pov(t_data *data)
{
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	if (data->player_char == 'N')
	{
		data->player.dir_x = -1;
		data->player.plane_y = 0.66;
	}
	else if (data->player_char == 'S')
	{
		data->player.dir_x = 1;
		data->player.plane_y = -0.66;
	}
	else if (data->player_char == 'E')
	{
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
	}
	else
	{
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
	}
}
