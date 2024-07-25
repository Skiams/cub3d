/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:28:58 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/25 15:29:02 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_foward(t_data *data, double moveSpeed)
{
	if (data->mini_map.map[(int)(data->player.pos_x + data->player.dir_x * moveSpeed)][(int)data->player.pos_y] != '1')
		data->player.pos_x += data->player.dir_x * moveSpeed;
	if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y + data->player.dir_y * moveSpeed)] != '1')
		data->player.pos_y += data->player.dir_y * moveSpeed;
}

void	move_back(t_data *data, double moveSpeed)
{
	if (data->mini_map.map[(int)(data->player.pos_x - data->player.dir_x * moveSpeed)][(int)data->player.pos_y] != '1')
		data->player.pos_x -= data->player.dir_x * moveSpeed;
	if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y - data->player.dir_y * moveSpeed)] != '1')
		data->player.pos_y -= data->player.dir_y * moveSpeed;
}

void	move_left(t_data *data, double moveSpeed)
{
	if (data->mini_map.map[(int)(data->player.pos_x - data->player.plane_x * moveSpeed)][(int)data->player.pos_y] != '1')
		data->player.pos_x -= data->player.plane_x * moveSpeed;
	if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y - data->player.plane_y * moveSpeed)] != '1')
		data->player.pos_y -= data->player.plane_y * moveSpeed;
}

void	move_right(t_data *data, double moveSpeed)
{
	if (data->mini_map.map[(int)(data->player.pos_x + data->player.plane_x * moveSpeed)][(int)data->player.pos_y] != '1')
		data->player.pos_x += data->player.plane_x * moveSpeed;
	if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y + data->player.plane_y * moveSpeed)] != '1')
		data->player.pos_y += data->player.plane_y * moveSpeed;
}

void	player_rotation(t_game_key game, t_player *player)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed;

	oldDirX = player->dir_x;
	oldPlaneX = player->plane_x;
	rotSpeed = 0.008;
	if ((game.left || game.mouse < 0) && !game.right)
	{
		player->dir_x = player->dir_x * cos(rotSpeed) - player->dir_y * sin(rotSpeed);
		player->dir_y = oldDirX * sin(rotSpeed) + player->dir_y * cos(rotSpeed);
		player->plane_x = player->plane_x * cos(rotSpeed) - player->plane_y * sin(rotSpeed);
		player->plane_y = oldPlaneX * sin(rotSpeed) + player->plane_y * cos(rotSpeed);
	}
	else if (game.right || game.mouse > 0)
	{
		player->dir_x = player->dir_x * cos(-rotSpeed) - player->dir_y * sin(-rotSpeed);
		player->dir_y = oldDirX * sin(-rotSpeed) + player->dir_y * cos(-rotSpeed);
		player->plane_x = player->plane_x * cos(-rotSpeed) - player->plane_y * sin(-rotSpeed);
		player->plane_y = oldPlaneX * sin(-rotSpeed) + player->plane_y * cos(-rotSpeed);
	}
}
