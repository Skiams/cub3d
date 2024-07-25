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

void	found_player_pos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->mini_map.map[i])
	{
		j = 0;
		while (data->mini_map.map[i][j])
		{
			if (is_player(data->mini_map.map[i][j]))
			{
				data->player_char = data->mini_map.map[i][j];
				data->mini_map.pos_player.x = i;
				data->mini_map.pos_player.y = j;
				data->player.pos_x = i + 0.5;
				data->player.pos_y = j + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	calculate_map_arg(t_mini_map *mini_map)
{
	int	new_player_x;
	int	new_player_y;

	mini_map->nbr_columns = ft_strlen(mini_map->map[mini_map->pos_player.x]);
	mini_map->start.x = MAX(0, mini_map->pos_player.x - ZOOM_MINI / 2);
	mini_map->start.y = MAX(0, mini_map->pos_player.y - ZOOM_MINI / 2);
	mini_map->end.x = MIN(mini_map->nbr_lines,
		mini_map->pos_player.x + ZOOM_MINI / 2);
	mini_map->end.y = MIN(mini_map->nbr_columns,
		mini_map->pos_player.y + ZOOM_MINI / 2);
	new_player_x = mini_map->pos_player.x + mini_map->player_pixel.x / mini_map->block_height;
	new_player_y = mini_map->pos_player.y + mini_map->player_pixel.y / mini_map->block_width;
	if (new_player_x != mini_map->pos_player.x
		|| new_player_y != mini_map->pos_player.y)
	{
		mini_map->pos_player.x = new_player_x;
		mini_map->pos_player.y = new_player_y;
		mini_map->player_pixel.x = mini_map->player_pixel.x % mini_map->block_height;
		mini_map->player_pixel.y = mini_map->player_pixel.y % mini_map->block_width;
	}
	mini_map->playerScreen.x =
		(mini_map->pos_player.x - mini_map->start.x) * mini_map->block_height + mini_map->player_pixel.x;
	mini_map->playerScreen.y =
		(mini_map->pos_player.y - mini_map->start.y) * mini_map->block_width + mini_map->player_pixel.y;
}

void	change_player_pos(t_data *data)
{
	data->mini_map.map[data->mini_map.pos_player.x][data->mini_map.pos_player.y] = '0';
	data->mini_map.pos_player.x = (int)data->player.pos_x;
	data->mini_map.pos_player.y = (int)data->player.pos_y;
	if (data->mini_map.player_pixel.x < 0)
	{
		data->mini_map.pos_player.x -= 1;
		data->mini_map.player_pixel.x = data->mini_map.block_height - 1;
	}
	else if (data->mini_map.player_pixel.x >= data->mini_map.block_height)
	{
		data->mini_map.pos_player.x += 1;
		data->mini_map.player_pixel.x = 0;
	}
	if (data->mini_map.player_pixel.y < 0)
	{
		data->mini_map.pos_player.y -= 1;
		data->mini_map.player_pixel.y = data->mini_map.block_width - 1;
	}
	else if (data->mini_map.player_pixel.y >= data->mini_map.block_width)
	{
		data->mini_map.pos_player.y += 1;
		data->mini_map.player_pixel.y = 0;
	}
	data->mini_map.map[data->mini_map.pos_player.x][data->mini_map.pos_player.y] = data->player_char;
}

int	handle_player(t_data *data)
{
	double	moveSpeed;

	moveSpeed = 0.02;
	player_rotation(data->game, &data->player);
	if (data->game.key_w)
		move_foward(data, moveSpeed);
	if (data->game.key_s)
		move_back(data, moveSpeed);
	if (data->player_char == 'W' || data->player_char == 'E')
		moveSpeed *= -1;
	if (data->game.key_a)
		move_left(data, moveSpeed);
	if (data->game.key_d)
		move_right(data, moveSpeed);
	change_player_pos(data);
	return (0);
}
	// printf("----------\nx : %f\n", data->player.pos_x);
	// printf("y : %f\n", data->player.pos_y);
	// printf("mini_map.pos_player.x : %d\n", data->mini_map.pos_player.x);
	// printf("mini_map.pos_player.y : %d\n", data->mini_map.pos_player.y);

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

	// printf("plane x : %f\n", data.player.plane_x);
	// printf("plane y : %f\n", data.player.plane_y);


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

	// printf("----------\nx : %f\n", data->player.pos_x);
	// printf("y : %f\n", data->player.pos_y);
	// printf("mini_map.pos_player.x : %d\n", data->mini_map.pos_player.x);
	// printf("mini_map.pos_player.y : %d\n", data->mini_map.pos_player.y);

int	render(t_data *data)
{
	if (data->mlx_win == NULL)
		return (1);
	handle_player(data);
	draw_background(data);
	calculate_map_arg(&data->mini_map);
	ray_casting(data);
	if (data->mini_map.show_map)
		draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.img, 0, 0);
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

void	init_sprite_tex(t_data *data)
{
	data->sprites.textures[0] = (int *)mlx_get_data_addr(data->sprites.img_north.img, &data->sprites.img_north.bpp,
		&data->sprites.img_north.line_len, &data->sprites.img_north.endian);
	data->sprites.textures[1] = (int *)mlx_get_data_addr(data->sprites.img_south.img, &data->sprites.img_south.bpp,
		&data->sprites.img_south.line_len, &data->sprites.img_south.endian);
	data->sprites.textures[2] = (int *)mlx_get_data_addr(data->sprites.img_east.img, &data->sprites.img_east.bpp,
		&data->sprites.img_east.line_len, &data->sprites.img_east.endian);
	data->sprites.textures[3] = (int *)mlx_get_data_addr(data->sprites.img_west.img, &data->sprites.img_west.bpp,
		&data->sprites.img_west.line_len, &data->sprites.img_west.endian);
}

void	destroy_sprites_img(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->sprites.img_north.img);
	mlx_destroy_image(data->mlx_ptr, data->sprites.img_south.img);
	mlx_destroy_image(data->mlx_ptr, data->sprites.img_east.img);
	mlx_destroy_image(data->mlx_ptr, data->sprites.img_west.img);
}

static int handle_mouse_movement(int x, int y, t_data *data)
{
	(void)y;
	if (x < (WINDOW_WIDTH / 2) - 100)
		data->game.mouse = -1;
	else if (x > (WINDOW_WIDTH / 2) + 100)
		data->game.mouse = 1;
	else if (x == 0 || x == WINDOW_WIDTH)
		data->game.mouse = 0;
	else
		data->game.mouse = 0;
	return (0);
}

static int leave_window(t_data *data)
{
	data->game.mouse = 0;
	return (0);
}

int	execution(t_data *data)
{
	//player initial dir
	set_player_pov(data);
	//textures
	init_sprite_tex(data);
	//game loop
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, data);
	mlx_hook(data->mlx_win, MotionNotify, PointerMotionMask, &handle_mouse_movement, data);
	mlx_hook(data->mlx_win, LeaveNotify, LeaveWindowMask, &leave_window, data);
	mlx_hook(data->mlx_win, 17, 0, &close_window, data);
	mlx_loop(data->mlx_ptr);
	destroy_sprites_img(data);
	return (0);
}

