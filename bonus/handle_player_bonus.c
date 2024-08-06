/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:13:38 by dvalino-          #+#    #+#             */
/*   Updated: 2024/08/06 19:17:09 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

double	get_frame_time(t_data *data)
{
	double	frame_time;

	data->old_time = data->time;
	data->time = get_time();
	frame_time = (data->time - data->old_time) / 1000.0;
	return (frame_time);
}

int	handle_player(t_data *data)
{
	double	move_speed;
	double	rot_speed;
	double	frame_time;

	frame_time = get_frame_time(data);
	rot_speed = 2.0;
	move_speed = 4.0;
	player_rotation(data->game, &data->player, frame_time * rot_speed);
	if (data->game.key_w)
		move_foward(data, frame_time * move_speed);
	if (data->game.key_s)
		move_back(data, frame_time * move_speed);
	if (data->player_char == 'W' || data->player_char == 'E')
		move_speed *= -1;
	if (data->game.key_a)
		move_left(data, frame_time * move_speed);
	if (data->game.key_d)
		move_right(data, frame_time * move_speed);
	change_player_pos(data);
	check_animation(data);
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
	else if (data->player_char == 'W')
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
