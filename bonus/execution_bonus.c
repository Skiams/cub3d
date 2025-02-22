/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:34:36 by dvalino-          #+#    #+#             */
/*   Updated: 2024/08/07 16:37:26 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

// change to init part ?
void	init_sprite_tex(t_data *data)
{
	data->sprites.textures[0]
		= (int *)mlx_get_data_addr(data->sprites.img_north.img,
			&data->sprites.img_north.bpp,
			&data->sprites.img_north.line_len, &data->sprites.img_north.endian);
	data->sprites.textures[1]
		= (int *)mlx_get_data_addr(data->sprites.img_south.img,
			&data->sprites.img_south.bpp,
			&data->sprites.img_south.line_len, &data->sprites.img_south.endian);
	data->sprites.textures[2]
		= (int *)mlx_get_data_addr(data->sprites.img_east.img,
			&data->sprites.img_east.bpp,
			&data->sprites.img_east.line_len, &data->sprites.img_east.endian);
	data->sprites.textures[3]
		= (int *)mlx_get_data_addr(data->sprites.img_west.img,
			&data->sprites.img_west.bpp,
			&data->sprites.img_west.line_len, &data->sprites.img_west.endian);
	data->sprites.textures[4]
		= (int *)mlx_get_data_addr(data->doors.close_tex.img,
			&data->doors.close_tex.bpp,
			&data->doors.close_tex.line_len, &data->doors.close_tex.endian);
	data->sprites.textures[5]
		= (int *)mlx_get_data_addr(data->doors.open_tex.img,
			&data->doors.open_tex.bpp,
			&data->doors.open_tex.line_len, &data->doors.open_tex.endian);
}

int	execution(t_data *data)
{
	set_player_pov(data);
	init_doors_texture(data);
	init_sprite_tex(data);
	get_animation_textures(data);
	data->time = get_time();
	if (data->time == -1)
		return (0);
	data->old_time = data->time;
	get_door_total(data->mini_map.map, data, 0);
	data->doors.coord_tab = ft_calloc(sizeof(t_point), data->doors.total);
	data->doors.is_open = ft_calloc(sizeof(int), data->doors.total);
	get_door_total(data->mini_map.map, data, 1);
	data->anim_sprite.old_time = get_time();
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask,
		&handle_keyrelease, data);
	mlx_hook(data->mlx_win, MotionNotify, PointerMotionMask,
		&handle_mouse_movement, data);
	mlx_hook(data->mlx_win, LeaveNotify, LeaveWindowMask, &leave_window, data);
	mlx_hook(data->mlx_win, 17, 0, &close_window, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
