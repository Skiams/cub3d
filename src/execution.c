/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:34:36 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/25 15:08:01 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
}

// change to clean part ?
void	destroy_sprites_img(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->sprites.img_north.img);
	mlx_destroy_image(data->mlx_ptr, data->sprites.img_south.img);
	mlx_destroy_image(data->mlx_ptr, data->sprites.img_east.img);
	mlx_destroy_image(data->mlx_ptr, data->sprites.img_west.img);
}

	//player initial dir
	//textures
	//game loop
int	execution(t_data *data)
{
	set_player_pov(data);
	init_sprite_tex(data);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask,
		&handle_keyrelease, data);
	mlx_hook(data->mlx_win, MotionNotify, PointerMotionMask,
		&handle_mouse_movement, data);
	mlx_hook(data->mlx_win, LeaveNotify, LeaveWindowMask, &leave_window, data);
	mlx_hook(data->mlx_win, 17, 0, &close_window, data);
	mlx_loop(data->mlx_ptr);
	destroy_sprites_img(data);
	return (0);
}
