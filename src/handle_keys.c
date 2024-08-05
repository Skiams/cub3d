/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:48:29 by dvalino-          #+#    #+#             */
/*   Updated: 2024/08/05 20:24:03 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	open_sesame(t_data *data, double move_speed)
{
	int i;
	
	i = 0;
	if ((!open_door((int)(data->player.pos_x
		+ data->player.dir_x * move_speed), (int)data->player.pos_y, data) || !open_door((int)data->player.pos_x, (int)(data->player.pos_y
		+ data->player.dir_y * move_speed), data)) || (open_door((int)(data->player.pos_x
		+ data->player.dir_x * move_speed), (int)data->player.pos_y, data) || open_door((int)data->player.pos_x, (int)(data->player.pos_y
		+ data->player.dir_y * move_speed), data)))
	{
		while (i < data->doors.total)
		{		
			if ((data->doors.coord_tab[i].x == (int)data->player.pos_x + 1
				&& data->doors.coord_tab[i].y == (int)data->player.pos_y)
				|| (data->doors.coord_tab[i].x == (int)data->player.pos_x - 1
				&& data->doors.coord_tab[i].y == (int)data->player.pos_y)
				||(data->doors.coord_tab[i].x == (int)data->player.pos_x
				&& data->doors.coord_tab[i].y == (int)data->player.pos_y + 1)
				|| (data->doors.coord_tab[i].x == (int)data->player.pos_x
				&& data->doors.coord_tab[i].y == (int)data->player.pos_y - 1))
				data->doors.is_open[i] = !data->doors.is_open[i];
			i++;
		}
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		data->mlx_win = NULL;
	}
	if (keysym == XK_Up)
		data->game.up = 1;
	if (keysym == XK_Down)
		data->game.down = 1;
	if (keysym == XK_Left)
		data->game.left = 1;
	if (keysym == XK_Right)
		data->game.right = 1;
	if (keysym == XK_w)
		data->game.key_w = 1;
	if (keysym == XK_s)
		data->game.key_s = 1;
	if (keysym == XK_a)
		data->game.key_a = 1;
	if (keysym == XK_d)
		data->game.key_d = 1;
	if (keysym == XK_e)
		open_sesame(data, get_frame_time(data) * 4);
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_m)
		data->mini_map.show_map = !data->mini_map.show_map;
	if (keysym == XK_Up)
		data->game.up = 0;
	if (keysym == XK_Down)
		data->game.down = 0;
	if (keysym == XK_Left)
		data->game.left = 0;
	if (keysym == XK_Right)
		data->game.right = 0;
	if (keysym == XK_w)
		data->game.key_w = 0;
	if (keysym == XK_s)
		data->game.key_s = 0;
	if (keysym == XK_a)
		data->game.key_a = 0;
	if (keysym == XK_d)
		data->game.key_d = 0;
	return (0);
}

void	init_keys(t_data *data)
{
	data->game.down = 0;
	data->game.up = 0;
	data->game.left = 0;
	data->game.right = 0;
	data->game.key_a = 0;
	data->game.key_d = 0;
	data->game.key_s = 0;
	data->game.key_w = 0;
	data->mini_map.show_map = 0;
	data->time = 0;
	data->old_time = 0;
}
