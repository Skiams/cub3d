/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:34:36 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/08 14:34:38 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_exec.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
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

void	draw_square(int x, int y, int color, t_data *data)
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

void	init_draw_line(t_point a, t_point b, t_point *d, t_point *s)
{
	d->x = abs(a.x - b.x);
	d->y = abs(a.y - b.y);
	s->x = (a.x < b.x) ? 1 : -1;
	s->y = (a.y < b.y) ? 1 : -1;
}

void	draw_line(t_point a, t_point b, t_data *data)
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
			my_mlx_pixel_put(&data->img, a.y, a.x, 0x00FFFFFF);
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

void	draw_rays(t_data *data)
{
	int	r = 0, mx = 0, my = 0, mp = 0, dof;
	float rx = 0, ry = 0, ra = 0, xo = 0, yo = 0;

	int py = data->mini_map.playerScreen.y;
	int px = data->mini_map.playerScreen.x;
	for (r = 0; r < 1; r++)
	{
		dof = 0;
		float aTan = -1/tan(ra);
		if (ra > PI)
		{
			ry = (((int)py >> 6)<<6)-0.0001;
			rx = (py - ry) * aTan + px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int)py >> 6)<<6)+64;
			rx = (py - ry) * aTan + px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>data->mini_map.nbr_lines;
			my = (int)(ry)>>data->mini_map.nbr_columns;
			mp = my*data->mini_map.nbr_columns+mx;
			if (mp < data->mini_map.nbr_columns*data->mini_map.nbr_lines
				&& data->mini_map.map[mx][my] == '1')
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		t_point b;
		b.x = rx;
		b.y = ry;
		draw_line(data->mini_map.playerScreen, b, data);
	}
}

void	draw_player(t_data *data)
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
			my_mlx_pixel_put(&data->img, j + data->mini_map.playerScreen.y - 2,
				i + data->mini_map.playerScreen.x - 2, 0x00000000);
			j++;
		}
		i++;
	}
	t_point b;
	printf("dx : %f\n", data->player.delta_x);
	b.x = data->mini_map.playerScreen.x + (data->player.delta_x);
	b.y = data->mini_map.playerScreen.y + (data->player.delta_y);
	draw_line(data->mini_map.playerScreen, b, data);
	// draw_rays(data);
}

int	draw_background(t_data *data)
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

int		is_player(char c)
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

void	draw_map(t_data *data)
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
				draw_square(x, y, 0x00CC0000, data);
			else
				draw_square(x, y, 0x00FF9933, data);
		}
	}
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
}

int	init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (0);
	data->mlx_win = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3d");
	if (data->mlx_win == NULL)
		return (free(data->mlx_win), 0);
	data->img.img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	//map settings
	found_player_pos(data);
	init_keys(data);
	data->mini_map.nbr_columns = ft_strlen(data->mini_map.map[0]);
	data->mini_map.nbr_lines = array_len(data->mini_map.map);
	data->mini_map.block_height = (WINDOW_HEIGHT / 2) / ZOOM_MINI; // change later window_height for map_height
	data->mini_map.block_width = (WINDOW_WIDTH / 3) / ZOOM_MINI;
	data->mini_map.player_pixel.x = data->mini_map.block_height / 2;
	data->mini_map.player_pixel.y = data->mini_map.block_width / 2;
	data->player.pos_x = data->mini_map.player_pixel.x; // change
	data->player.pos_y = data->mini_map.player_pixel.y;
	return (1);
}


void	change_player_pos(t_mini_map *minimap)
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

int	is_wall(int x, int y, t_mini_map minimap)
{
	if (minimap.playerScreen.x + x < 0
		|| minimap.playerScreen.x + x >= WINDOW_HEIGHT)
		return (1);
	if (minimap.playerScreen.y + y < 0
		|| minimap.playerScreen.y + y >= WINDOW_WIDTH)
		return (1);
	if (minimap.player_pixel.x + x < 0)
		minimap.pos_player.x -= 1;
	else if (minimap.player_pixel.x + x >= minimap.block_height)
		minimap.pos_player.x += 1;
	if (minimap.player_pixel.y + y < 0)
		minimap.pos_player.y -= 1;
	else if (minimap.player_pixel.y + y >= minimap.block_width)
		minimap.pos_player.y += 1;
	return (minimap.map[minimap.pos_player.x][minimap.pos_player.y] != '0'
		&& !is_player(minimap.map[minimap.pos_player.x][minimap.pos_player.y]));
}

void	change_degrees(t_game_key game, t_player *player)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed;

	oldDirX = player->delta_x;
	oldPlaneX = player->plane_x;
	rotSpeed = 0.05;
	if (game.key_d)
	{
		player->angle -= 0.1;
		if (player->angle < 0)
			player->angle += 2*PI;
		player->delta_x = (player->delta_x * cos(rotSpeed)) - (player->delta_y * sin(rotSpeed));
		player->delta_y = (oldDirX * sin(rotSpeed)) + (player->delta_y * cos(rotSpeed));
		player->plane_x = (player->plane_x * cos(rotSpeed)) - (player->plane_y * sin(rotSpeed));
		player->plane_y = (oldPlaneX * sin(rotSpeed)) + (player->plane_y * cos(rotSpeed));
	}
	if (game.key_a)
	{
		player->angle += 0.1;
		if (player->angle > 2*PI)
			player->angle -= 2*PI;
		player->delta_x = (player->delta_x * cos(-rotSpeed)) - (player->delta_y * sin(-rotSpeed));
		player->delta_y = (oldDirX * sin(-rotSpeed)) + (player->delta_y * cos(-rotSpeed));
		player->plane_x = (player->plane_x * cos(-rotSpeed)) - (player->plane_y * sin(-rotSpeed));
		player->plane_y = (oldPlaneX * sin(-rotSpeed)) + (player->plane_y * cos(-rotSpeed));
	}
	if (game.key_w)
	{
		player->pos_x += player->delta_x;
		player->pos_y += player->delta_y;
	}
	if (game.key_s)
	{
		player->pos_x -= player->delta_x;
		player->pos_y -= player->delta_y;
	}
}

int	handle_player(t_data *data)
{
	change_degrees(data->game, &data->player);
	if (data->game.up && !is_wall(-3, 0, data->mini_map))
		data->mini_map.player_pixel.x -= 1;
	if (data->game.down && !is_wall(3, 0, data->mini_map))
		data->mini_map.player_pixel.x += 1;
	if (data->game.left && !is_wall(0, -3, data->mini_map))
		data->mini_map.player_pixel.y -= 1;
	if (data->game.right && !is_wall(0, 3, data->mini_map))
		data->mini_map.player_pixel.y += 1;
	change_player_pos(&data->mini_map);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		data->mlx_win = NULL;
	}
	if (keysym == XK_m)
		data->mini_map.show_map = !data->mini_map.show_map;
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

void	ray_casting(t_data *data)
{
	t_player	player;
	double		cameraX;
	int			mapX;
	int			mapY;
	int			y;

	player.pos_x = (double)data->mini_map.player_pixel.x;
	player.pos_y = (double)data->mini_map.player_pixel.y;
	player.delta_x = data->player.delta_x;
	player.delta_y = data->player.delta_y;
	player.plane_x = data->player.plane_x;
	player.plane_y = data->player.plane_y;
	y = -1;
	while (++y < WINDOW_WIDTH)
	{
		cameraX = 2 * y / (double)WINDOW_WIDTH - 1;
		player.ray_dir_x = player.delta_x + player.plane_x * cameraX;
		player.ray_dir_y = player.delta_y + player.plane_y * cameraX;
		mapX = data->mini_map.pos_player.x;
		mapY = data->mini_map.pos_player.y;
		player.deltaDis_x = 1 / player.ray_dir_x;
		if (player.deltaDis_x < 0)
			player.deltaDis_x *= -1;
		player.deltaDis_y = 1 / player.ray_dir_y;
		if (player.deltaDis_y < 0)
			player.deltaDis_y *= -1;
		double perpWallDist;
		t_point step;
		step.x = 1;
		player.sideDist_x = (mapX + 1.0 - player.pos_x) * player.deltaDis_x;
		step.y = 1;
		player.sideDist_y = (mapY + 1.0 - player.pos_y) * player.deltaDis_y;
		if (player.ray_dir_x < 0)
		{
			step.x = -1;
			player.sideDist_x = (player.pos_x - mapX) * player.deltaDis_x;
		}
		if (player.ray_dir_y < 0)
		{
			step.y = -1;
			player.sideDist_y = (player.pos_y - mapY) * player.deltaDis_y;
		}
		printf("++++++++\nplayer.sideDist_x : %f\n", player.sideDist_x);
		// DDA
		int hit = 0;
		int side;
		while (!hit)
		{
			if (player.sideDist_x < player.sideDist_y)
			{
				player.sideDist_x += player.deltaDis_x;
				mapX += step.x;
				side = 0;
			}
			else
			{
				player.sideDist_y += player.deltaDis_y;
				mapY += step.y;
				side = 1;
			}
			printf("player.sideDist_x : %f\n------------\nmapX : %d\nmapY : %d\nmap[X][Y] : %c\n",
				player.sideDist_x, mapX, mapY, data->mini_map.map[mapX][mapY]);
			if (data->mini_map.map[mapX][mapY] == '1')
				hit = 1;
		}
		if (!side)
			perpWallDist = (mapX - player.pos_x + (1 - step.x) / 2 ) / player.ray_dir_x;
		else
			perpWallDist = (mapY - player.pos_y + (1 - step.y) / 2 ) / player.ray_dir_y;
		printf("perpWall : %f\n", perpWallDist);
		int	lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);
		printf("lineheight : %d\n", lineHeight);
		int	drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
		printf("drawStart : %d\n", drawStart);
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawEnd > WINDOW_HEIGHT)
			drawEnd = WINDOW_HEIGHT;
		int x;
		x = drawStart;
		while (x < drawEnd)
		{
			my_mlx_pixel_put(&data->img, y, x, 0x006600CC / ((side == 1) + 1));
			x++;
		}
	}
}

int	render(t_data *data)
{
	if (data->mlx_win == NULL)
		return (1);
	//draw background
	handle_player(data);
	draw_background(data);
	calculate_map_arg(&data->mini_map);
	ray_casting(data);
	if (data->mini_map.show_map)
		draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.img, 0, 0);
	return (0);
}

int	execution(char **map)
{
	t_data	data;

	data.mini_map.map = map;
	data.player.angle = 0;
	data.player.delta_x = 1;
	data.player.delta_y = 0;
	data.player.plane_x = 0;
	data.player.plane_y = 0.66;
	if (!init(&data))
		return (0);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}

int	main()
{
	char *map[] = {
		"11111111111111",
		"10000000000001",
		"10000000000001",
		"100000N0000001",
		"10000000000001",
		"11111000000001",
		"10000000000001",
		"11111111111111", NULL};
	char **map2;

	map2 = ft_calloc(sizeof(char*), array_len(map) + 1);
	for (int i = 0; i < array_len(map); i++)
	{
		map2[i] = ft_strdup(map[i]);
	}
	execution(map2);
	return (0);
}