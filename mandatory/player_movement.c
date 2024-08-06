/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:28:58 by dvalino-          #+#    #+#             */
/*   Updated: 2024/08/06 18:36:47 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_foward(t_data *data, double move_speed)
{
	if (data->mini_map.map[(int)(data->player.pos_x
			+ data->player.dir_x * move_speed)][(int)data->player.pos_y] != '1')
			data->player.pos_x += data->player.dir_x * move_speed;
	if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y
		+ data->player.dir_y * move_speed)] != '1')
			data->player.pos_y += data->player.dir_y * move_speed;
}

void	move_back(t_data *data, double move_speed)
{
	if (data->mini_map.map[(int)(data->player.pos_x
			- data->player.dir_x * move_speed)][(int)data->player.pos_y] != '1')
		data->player.pos_x -= data->player.dir_x * move_speed;
	if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y
		- data->player.dir_y * move_speed)] != '1')
		data->player.pos_y -= data->player.dir_y * move_speed;
}

void	move_left(t_data *data, double move_speed)
{
	if (data->mini_map.map[(int)(data->player.pos_x - data->player.plane_x
			* move_speed)][(int)data->player.pos_y] != '1')
		data->player.pos_x -= data->player.plane_x * move_speed;
	if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y
		- data->player.plane_y * move_speed)] != '1')
		data->player.pos_y -= data->player.plane_y * move_speed;
}

void	move_right(t_data *data, double move_speed)
{
	if (data->mini_map.map[(int)(data->player.pos_x + data->player.plane_x
			* move_speed)][(int)data->player.pos_y] != '1')
		data->player.pos_x += data->player.plane_x * move_speed;
	if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y
		+ data->player.plane_y * move_speed)] != '1')
		data->player.pos_y += data->player.plane_y * move_speed;
}

void	player_rotation(t_game_key game, t_player *player, double spd)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	if ((game.left) && !game.right)
	{
		player->dir_x = player->dir_x * cos(spd)
			- player->dir_y * sin(spd);
		player->dir_y = old_dir_x * sin(spd) + player->dir_y * cos(spd);
		player->plane_x = player->plane_x
			* cos(spd) - player->plane_y * sin(spd);
		player->plane_y = old_plane_x * sin(spd)
			+ player->plane_y * cos(spd);
	}
	else if (game.right)
	{
		player->dir_x = player->dir_x * cos(-spd)
			- player->dir_y * sin(-spd);
		player->dir_y = old_dir_x * sin(-spd) + player->dir_y * cos(-spd);
		player->plane_x = player->plane_x * cos(-spd)
			- player->plane_y * sin(-spd);
		player->plane_y = old_plane_x * sin(-spd)
			+ player->plane_y * cos(-spd);
	}
}
