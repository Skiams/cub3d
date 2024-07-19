/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:34:36 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/19 17:06:16 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		i;

	i = img->bpp - 8;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*dst++ = (color >> i) & 0xFF;
		else
			*dst++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

static void	draw_square(int x, int y, int color, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->mini_map.block_height && i + x < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < data->mini_map.block_width && j + y < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(&data->img, j + y, i + x, color);
			j++;
		}
		i++;
	}
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static void	init_draw_line(t_point a, t_point b, t_point *d, t_point *s)
{
	d->x = abs(a.x - b.x);
	d->y = abs(a.y - b.y);
	s->x = (a.x < b.x) ? 1 : -1;
	s->y = (a.y < b.y) ? 1 : -1;
}

static void	draw_line(t_point a, t_point b, t_data *data)
{
	t_point	d;
	t_point	s;
	int	error;
	int	e2;

	init_draw_line(a, b, &d, &s);
	error = d.x - d.y;
	while (1)
	{
		if ((a.x < WINDOW_WIDTH && a.x >= 0) && (a.y < WINDOW_WIDTH && a.y >= 0))
			my_mlx_pixel_put(&data->img, a.y, a.x, 0x00000000);
		if (a.x == b.x && a.y == b.y)
			break ;
		e2 = 2 * error;
		if (e2 > -d.y)
		{
			error -= d.y;
			a.x += s.x;
		}
		if (e2 < d.x)
		{
			error += d.x;
			a.y += s.y;
		}
	}
}

static int	acceptable_coordinates(int x, int y)
{
	if (x < 0 || x > WINDOW_WIDTH)
		return (0);
	if (y < 0 || y > WINDOW_WIDTH)
		return (0);
	return (1);
}

static void	draw_player(t_data *data)
{
	int	i;
	int	j;
	int	player_h;
	int	player_w;

	player_w = 5;
	player_h = 5;
	i = 0;
	while (i < player_h)
	{
		j = 0;
		while (j < player_w)
		{
			if (acceptable_coordinates(i + data->mini_map.playerScreen.x - 2,
				j + data->mini_map.playerScreen.y - 2))
			my_mlx_pixel_put(&data->img, j + data->mini_map.playerScreen.y - 2,
				i + data->mini_map.playerScreen.x - 2, 0x00000000);
			j++;
		}
		i++;
	}
	t_point b;
	b.x = data->mini_map.playerScreen.x + data->player.dir_x * 5;
	b.y = data->mini_map.playerScreen.y + data->player.dir_y * 5;
	draw_line(data->mini_map.playerScreen, b, data);
}

static int	draw_background(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT/2)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(&data->img, j, i, 0x000000CC);
			my_mlx_pixel_put(&data->img, j++,(WINDOW_HEIGHT/2) + i, 0x0000CC00);
		}
		i++;
	}
	return (0);
}

// Creation of minimap

static int		is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

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

static void	calculate_map_arg(t_mini_map *mini_map)
{
	int	new_player_x;
	int	new_player_y;

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

static void	draw_map(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = data->mini_map.start.x - 1;
	while (++i < data->mini_map.end.x)
	{
		j = data->mini_map.start.y - 1;
		while (++j < data->mini_map.end.y)
		{
			x = (i - data->mini_map.start.x) * data->mini_map.block_height;
			y = (j - data->mini_map.start.y) * data->mini_map.block_width;
			if (data->mini_map.map[i][j] == '1')
				draw_square(x, y, 0x00CC0000/2, data);
			else
				draw_square(x, y, 0x00FF9933, data);
			printf("%c ", data->mini_map.map[i][j]);
		}
		printf("\n");
	}
	printf("--------------------\n");
	draw_player(data);
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

// int	init(t_data *data)
// {
// 	data->mlx_ptr = mlx_init();
// 	if (data->mlx_ptr == NULL)
// 		return (0);
// 	data->mlx_win = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH,
// 			WINDOW_HEIGHT, "cub3d");
// 	if (data->mlx_win == NULL)
// 		return (free(data->mlx_win), 0);
// 	data->img.img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
// 	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
// 			&data->img.line_len, &data->img.endian);
// 	//map settings
// 	found_player_pos(data);
// 	init_keys(data);
// 	data->mini_map.nbr_columns = ft_strlen(data->mini_map.map[0]);
// 	data->mini_map.nbr_lines = array_len(data->mini_map.map);
// 	data->mini_map.block_height = (WINDOW_HEIGHT / 2) / ZOOM_MINI; // change later window_height for map_height
// 	data->mini_map.block_width = (WINDOW_WIDTH / 3) / ZOOM_MINI;
// 	data->mini_map.player_pixel.x = data->mini_map.block_height / 2;
// 	data->mini_map.player_pixel.y = data->mini_map.block_width / 2;
// 	return (1);
// }


static void	change_player_pos(t_mini_map *minimap)
{
	minimap->map[minimap->pos_player.x][minimap->pos_player.y] = '0';
	if (minimap->player_pixel.x < 0)
	{
		minimap->pos_player.x -= 1;
		minimap->player_pixel.x = minimap->block_height - 1;
	}
	else if (minimap->player_pixel.x >= minimap->block_height)
	{
		minimap->pos_player.x += 1;
		minimap->player_pixel.x = 0;
	}
	if (minimap->player_pixel.y < 0)
	{
		minimap->pos_player.y -= 1;
		minimap->player_pixel.y = minimap->block_width - 1;
	}
	else if (minimap->player_pixel.y >= minimap->block_width)
	{
		minimap->pos_player.y += 1;
		minimap->player_pixel.y = 0;
	}
	minimap->map[minimap->pos_player.x][minimap->pos_player.y] = 'N';
}

// static int	is_wall(int x, int y, t_mini_map minimap)
// {
// 	if (minimap.playerScreen.x + x < 0
// 		|| minimap.playerScreen.x + x >= WINDOW_HEIGHT)
// 		return (1);
// 	if (minimap.playerScreen.y + y < 0
// 		|| minimap.playerScreen.y + y >= WINDOW_WIDTH)
// 		return (1);
// 	if (minimap.player_pixel.x + x < 0)
// 		minimap.pos_player.x -= 1;
// 	else if (minimap.player_pixel.x + x >= minimap.block_height)
// 		minimap.pos_player.x += 1;
// 	if (minimap.player_pixel.y + y < 0)
// 		minimap.pos_player.y -= 1;
// 	else if (minimap.player_pixel.y + y >= minimap.block_width)
// 		minimap.pos_player.y += 1;
// 	return (minimap.map[minimap.pos_player.x][minimap.pos_player.y] != '0'
// 		&& !is_player(minimap.map[minimap.pos_player.x][minimap.pos_player.y]));
// }

static void	change_degrees(t_game_key game, t_player *player)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed;

	oldDirX = player->dir_x;
	oldPlaneX = player->plane_x;
	rotSpeed = 0.005;
	if (game.key_a && !game.key_d)
	{
		player->dir_x = player->dir_x * cos(rotSpeed) - player->dir_y * sin(rotSpeed);
		player->dir_y = oldDirX * sin(rotSpeed) + player->dir_y * cos(rotSpeed);
		player->plane_x = player->plane_x * cos(rotSpeed) - player->plane_y * sin(rotSpeed);
		player->plane_y = oldPlaneX * sin(rotSpeed) + player->plane_y * cos(rotSpeed);
	}
	else if (game.key_d)
	{
		player->dir_x = player->dir_x * cos(-rotSpeed) - player->dir_y * sin(-rotSpeed);
		player->dir_y = oldDirX * sin(-rotSpeed) + player->dir_y * cos(-rotSpeed);
		player->plane_x = player->plane_x * cos(-rotSpeed) - player->plane_y * sin(-rotSpeed);
		player->plane_y = oldPlaneX * sin(-rotSpeed) + player->plane_y * cos(-rotSpeed);
	}
}

static int	handle_player(t_data *data)
{
	double	moveSpeed;

	moveSpeed = 0.01;
	change_degrees(data->game, &data->player);
	if (data->game.up)// && !is_wall(-3, 0, data->mini_map))
	{
		// data->mini_map.player_pixel.x -= 1;
		if (data->mini_map.map[(int)(data->player.pos_x + data->player.dir_x * moveSpeed)][(int)data->player.pos_y] != '1')
			data->player.pos_x += data->player.dir_x * moveSpeed;
		if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y + data->player.dir_y * moveSpeed)] != '1')
			data->player.pos_y += data->player.dir_y * moveSpeed;
	}
	if (data->game.down)// && !is_wall(3, 0, data->mini_map))
	{
		if (data->mini_map.map[(int)(data->player.pos_x - data->player.dir_x * moveSpeed)][(int)data->player.pos_y] != '1')
			data->player.pos_x -= data->player.dir_x * moveSpeed;
		if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y - data->player.dir_y * moveSpeed)] != '1')
			data->player.pos_y -= data->player.dir_y * moveSpeed;
	}
	if (data->game.left)// && !is_wall(0, -3, data->mini_map))
	{
		if (data->mini_map.map[(int)(data->player.pos_x - data->player.plane_x * moveSpeed)][(int)data->player.pos_y] != '1')
			data->player.pos_x -= data->player.plane_x * moveSpeed;
		if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y - data->player.plane_y * moveSpeed)] != '1')
			data->player.pos_y -= data->player.plane_y * moveSpeed;
	}
	if (data->game.right)// && !is_wall(0, 3, data->mini_map))
	{
		if (data->mini_map.map[(int)(data->player.pos_x + data->player.plane_x * moveSpeed)][(int)data->player.pos_y] != '1')
			data->player.pos_x += data->player.plane_x * moveSpeed;
		if (data->mini_map.map[(int)data->player.pos_x][(int)(data->player.pos_y + data->player.plane_y * moveSpeed)] != '1')
			data->player.pos_y += data->player.plane_y * moveSpeed;
	}
	data->mini_map.playerScreen.x = (int)data->player.pos_y;
	data->mini_map.playerScreen.y = (int)data->player.pos_y;
	printf("----------\nx : %f\n", data->player.pos_x);
	printf("y : %f\n", data->player.pos_y);
	change_player_pos(&data->mini_map);
	return (0);
}

static int	handle_keypress(int keysym, t_data *data)
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

static int	handle_keyrelease(int keysym, t_data *data)
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

static void	ray_casting(t_data *data)
{
	double		cameraX;
	int			mapX;
	int			mapY;
	int			y;
	int			x;
	double 		perpWallDist;
	t_point 	step;

	y = -(WINDOW_WIDTH / 2) - 1;
	while (++y < (WINDOW_WIDTH / 2))
	{
		cameraX = 2 * y / (double)(WINDOW_WIDTH - 1);
		data->player.ray_dir_x = data->player.dir_x + data->player.plane_x * cameraX;
		data->player.ray_dir_y = data->player.dir_y + data->player.plane_y * cameraX;
		mapX = (int)data->player.pos_x;
		mapY = (int)data->player.pos_y;
		data->player.deltaDis_x = (1 / data->player.ray_dir_x);
		if (data->player.deltaDis_x < 0)
			data->player.deltaDis_x *= -1;
		data->player.deltaDis_y = (1 / data->player.ray_dir_y);
		if (data->player.deltaDis_y < 0)
			data->player.deltaDis_y *= -1;
		if (data->player.ray_dir_x < 0)
		{
			step.x = -1;
			data->player.sideDist_x = (data->player.pos_x - mapX) * data->player.deltaDis_x;
		}
		else
		{
			step.x = 1;
		data->player.sideDist_x = (mapX + 1.0 - data->player.pos_x) * data->player.deltaDis_x;
		}
		if (data->player.ray_dir_y < 0)
		{
			step.y = -1;
			data->player.sideDist_y = (data->player.pos_y - mapY) * data->player.deltaDis_y;
		}
		else
		{
			step.y = 1;
			data->player.sideDist_y = (mapY + 1.0 - data->player.pos_y) * data->player.deltaDis_y;
		}
		int hit = 0;
		int side;
		while (!hit)
		{
			if (data->player.sideDist_x < data->player.sideDist_y)
			{
				data->player.sideDist_x += data->player.deltaDis_x;
				mapX += step.x;
				side = 0;
			}
			else
			{
				data->player.sideDist_y += data->player.deltaDis_y;
				mapY += step.y;
				side = 1;
			}
			if (data->mini_map.map[mapX][mapY] == '1')
				hit = 1;
		}
		if (!side) //(data->player.sideDist_x - data->player.deltaDis_x);
			perpWallDist = (data->player.sideDist_x - data->player.deltaDis_x);//(mapX - data->player.pos_x + (1 - step.x) / 2 ) / data->player.ray_dir_x;
		else //(data->player.sideDist_y - data->player.deltaDis_y);
			perpWallDist = (data->player.sideDist_y - data->player.deltaDis_y);//(mapY - data->player.pos_y + (1 - step.y) / 2 ) / data->player.ray_dir_y;
		int	lineHeight = (int)WINDOW_HEIGHT / perpWallDist;
		int	drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawEnd > WINDOW_HEIGHT)
			drawEnd = WINDOW_HEIGHT;
		x = drawStart - 1;
		int color;
		if (!side && step.x < 0)
			color = 0x00660033; // S
		else if (!side && step.x > 0)
			color = 0x00CC0066; // N
		else if (side && step.y > 0)
			color = 0x00009999; // E
		else
			color = 0x00666600; // W
		while (++x < drawEnd)
			my_mlx_pixel_put(&data->img, y + (WINDOW_WIDTH/2), x, color);
	}
		printf("plane x : %f\n", data->player.plane_x);
		printf("plane y : %f\n", data->player.plane_y);
}

static int	render(t_data *data)
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

int	execution(t_data *data)
{
// N : -1 0 0 0.66
// S : 1 0 0 -0.66
// E : 0 -1 0.66 0
// W : 0 1 -0.66 0
	// data->mini_map.map = map;
	data->player.dir_x = 0;
	data->player.dir_y = -1;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0;
	// if (!init(&data))
	// 	return (0);
	if (data->mini_map.map == NULL)
		return (printf("error null mlx_ptr\n"), 0);
	mlx_loop_hook(data->mlx_ptr, &render, &data);
	dprintf(2, "post mlx loop hook\n");
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	dprintf(2, "post mlx hook\n");
	mlx_loop(data->mlx_ptr);
	dprintf(2, "post mlx loop\n");
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (0);
}

// int	main()
// {
// 	char *map[] = {
// 		"11111111111111",
// 		"10000000000011",
// 		"1000000001001",
// 		"100000N011111",
// 		"100000001",
// 		"11111000111111",
// 		"10000000000001",
// 		"11111111111111", NULL};
// 	char **map2;

// 	map2 = ft_calloc(sizeof(char*), array_len(map) + 1);
// 	for (int i = 0; i < array_len(map); i++)
// 		map2[i] = ft_strdup(map[i]);
// 	execution(map2);
// 	return (0);
// }