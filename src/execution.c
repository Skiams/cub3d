/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:34:36 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/24 20:52:30 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

int	create_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	return (r << 16 | g << 8 | b);
}

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

int	acceptable_coordinates(int x, int y)
{
	if (x < 0 || x > WINDOW_WIDTH)
		return (0);
	if (y < 0 || y > WINDOW_WIDTH)
		return (0);
	return (1);
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
		if (acceptable_coordinates(a.x, a.y))
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

void	draw_player(t_data *data)
{
	int		i;
	int		j;
	int		player_h;
	int		player_w;
	t_point	b;

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
	b.x = data->mini_map.playerScreen.x + data->player.dir_x * 5;
	b.y = data->mini_map.playerScreen.y + data->player.dir_y * 5;
	draw_line(data->mini_map.playerScreen, b, data);
}

int	draw_background(t_data *data)
{
	int	i;
	int	j;
	int	ceiling_color;
	int	floor_color;

	i = 0;
	ceiling_color = create_rgb(data->sprites.ceiling[0],
		data->sprites.ceiling[1], data->sprites.ceiling[2]);
	floor_color = create_rgb(data->sprites.floor[0],
		data->sprites.floor[1], data->sprites.floor[2]);
	while (i < WINDOW_HEIGHT/2)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(&data->img, j, i, ceiling_color);
			my_mlx_pixel_put(&data->img, j++,(WINDOW_HEIGHT/2) + i, floor_color);
		}
		i++;
	}
	return (0);
}

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

void	draw_map(t_data *data)
{
	int		i;
	int		j;
	int 	len;
	t_point	point;

	i = data->mini_map.start.x;
	while (data->mini_map.map[i] && i < data->mini_map.end.x)
	{
		len = ft_strlen(data->mini_map.map[i]);
		j = data->mini_map.start.y - 1;
		while (++j < len && j < data->mini_map.end.y)
		{
			point.x = (i - data->mini_map.start.x) * data->mini_map.block_height;
			point.y = (j - data->mini_map.start.y) * data->mini_map.block_width;
			if (j < len && data->mini_map.map[i][j] == '1')
				draw_square(point.x, point.y, 0x00CC0000/2, data);
			else if (data->mini_map.map[i][j]
				&& (data->mini_map.map[i][j] == '0' || is_player(data->mini_map.map[i][j])))
				draw_square(point.x, point.y, 0x00FF9933, data);
			// if (j <= len)
				// printf("%c ", data->mini_map.map[i][j]);
		}
		// if (j < len)
		// 	printf("\n");
		i++;
	}
	// printf("-----------------------------------\n");
	draw_player(data);
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

void	change_degrees(t_game_key game, t_player *player)
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

int	handle_player(t_data *data)
{
	double	moveSpeed;

	moveSpeed = 0.02;
	change_degrees(data->game, &data->player);
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

int	calculate_ray_hit(t_data *data, t_ray_cast *ray_cast)
{
	int	side;
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (data->player.sideDist_x < data->player.sideDist_y)
		{
			data->player.sideDist_x += data->player.deltaDis_x;
			ray_cast->map.x += ray_cast->step.x;
			side = 0;
		}
		else
		{
			data->player.sideDist_y += data->player.deltaDis_y;
			ray_cast->map.y += ray_cast->step.y;
			side = 1;
		}
		if (data->mini_map.map[ray_cast->map.x][ray_cast->map.y] == '1')
			hit = 1;
	}
	return (side);
}

	// if (!ray->side && ray->step.x > 0)
	// 	ray->texnum = 0; //color = 0x00CC0066; // N
	// else if (!ray->side && ray->step.x < 0)
	// 	ray->texnum = 1; //color = 0x00660033; // S
	// else if (ray->side && ray->step.y > 0)
	// 	ray->texnum = 2; //color = 0x00009999; // E
	// else
	// 	ray->texnum = 3; //color = 0x00666600; // W
void	draw_ray_wall(t_data *data, t_ray_cast *ray)
{
	double			step_in_tex;
	double			texPos;

	ray->x = ray->drawStart - 1;
	if (!ray->side)
		ray->wallX = data->player.pos_y + ray->perpWallDist * data->player.ray_dir_y;
	else
		ray->wallX = data->player.pos_x + ray->perpWallDist * data->player.ray_dir_x;
	ray->wallX -= floor(ray->wallX);
	ray->tex.x = (int)(ray->wallX * (double)TEX_HEIGHT);
	if (!ray->side && data->player.ray_dir_x > 0)
		ray->tex.x = TEX_HEIGHT - ray->tex.x;
	if (ray->side && data->player.ray_dir_y < 0)
		ray->tex.x = TEX_HEIGHT - ray->tex.x;
	step_in_tex = 1.0 * TEX_HEIGHT / ray->lineHeight;
	texPos = (double)(ray->drawStart - WINDOW_HEIGHT/2 + ray->lineHeight/2) * step_in_tex;
	while (++ray->x < ray->drawEnd)
	{
		ray->tex.y = (int)(texPos) & (TEX_HEIGHT - 1);
		texPos += step_in_tex;
		ray->color = data->sprites.textures[ray->texnum][TEX_HEIGHT * ray->tex.y + ray->tex.x];
		my_mlx_pixel_put(&data->img, ray->y + (WINDOW_WIDTH/2), ray->x, ray->color);
	}
}

void	calculate_step_and_dist(t_data *data, t_ray_cast *ray)
{
		if (data->player.ray_dir_x < 0)
		{
			ray->step.x = -1;
			data->player.sideDist_x = (data->player.pos_x - ray->map.x) * data->player.deltaDis_x;
		}
		else
		{
			ray->step.x = 1;
			data->player.sideDist_x = (ray->map.x + 1.0 - data->player.pos_x) * data->player.deltaDis_x;
		}
		if (data->player.ray_dir_y < 0)
		{
			ray->step.y = -1;
			data->player.sideDist_y = (data->player.pos_y - ray->map.y) * data->player.deltaDis_y;
		}
		else
		{
			ray->step.y = 1;
			data->player.sideDist_y = (ray->map.y + 1.0 - data->player.pos_y) * data->player.deltaDis_y;
		}

}

void	choose_texture(t_ray_cast *ray)
{
	if (!ray->side && ray->step.x > 0)
		ray->texnum = 0; //color = 0x00CC0066; // N
	else if (!ray->side && ray->step.x < 0)
		ray->texnum = 1; //color = 0x00660033; // S
	else if (ray->side && ray->step.y > 0)
		ray->texnum = 2; //color = 0x00009999; // E
	else
		ray->texnum = 3; //color = 0x00666600; // W
}

void	calculate_ray_pos_and_dir(t_data *data, t_ray_cast *ray)
{
		ray->cameraX = 2 * ray->y / (double)(WINDOW_WIDTH - 1);
		if (data->player_char == 'W' || data->player_char == 'E')
			ray->cameraX *= -1;
		data->player.ray_dir_y = data->player.dir_y + data->player.plane_y * ray->cameraX;
		data->player.ray_dir_x = data->player.dir_x + data->player.plane_x * ray->cameraX;
		ray->map.x = (int)data->player.pos_x;
		ray->map.y = (int)data->player.pos_y;
		data->player.deltaDis_x = fabs(1 / data->player.ray_dir_x);
		data->player.deltaDis_y = fabs(1 / data->player.ray_dir_y);
}

void	ray_casting(t_data *data)
{
	t_ray_cast	ray;

	ray.y = -(WINDOW_WIDTH / 2) - 1;
	while (++ray.y < (WINDOW_WIDTH / 2))
	{
		calculate_ray_pos_and_dir(data, &ray);
		calculate_step_and_dist(data, &ray);
		ray.side = calculate_ray_hit(data, &ray);
		if (!ray.side)
			ray.perpWallDist = (data->player.sideDist_x - data->player.deltaDis_x);
		else
			ray.perpWallDist = (data->player.sideDist_y - data->player.deltaDis_y);
		ray.lineHeight = (int)WINDOW_HEIGHT / ray.perpWallDist;
		ray.drawStart = -ray.lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (ray.drawStart < 0)
			ray.drawStart = 0;
		ray.drawEnd = ray.lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (ray.drawEnd > WINDOW_HEIGHT)
			ray.drawEnd = WINDOW_HEIGHT;
		//Draw wall
		choose_texture(&ray);
		draw_ray_wall(data, &ray);
	}
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
	// double	oldDirX;
	// double	oldPlaneX;
	// double	rotSpeed;

	// oldDirX = data->player.dir_x;
	// oldPlaneX = data->player.plane_x;
	// rotSpeed = 0.015;
	// if (x < 480)
	// {
	// 	if (data->previous_dir < x)
	// 	{
	// 		data->player.dir_x = data->player.dir_x * cos(-rotSpeed) - data->player.dir_y * sin(-rotSpeed);
	// 		data->player.dir_y = oldDirX * sin(-rotSpeed) + data->player.dir_y * cos(-rotSpeed);
	// 		data->player.plane_x = data->player.plane_x * cos(-rotSpeed) - data->player.plane_y * sin(-rotSpeed);
	// 		data->player.plane_y = oldPlaneX * sin(-rotSpeed) + data->player.plane_y * cos(-rotSpeed);
	// 	}
	// 	data->player.dir_x = data->player.dir_x * cos(rotSpeed) - data->player.dir_y * sin(rotSpeed);
	// 	data->player.dir_y = oldDirX * sin(rotSpeed) + data->player.dir_y * cos(rotSpeed);
	// 	data->player.plane_x = data->player.plane_x * cos(rotSpeed) - data->player.plane_y * sin(rotSpeed);
	// 	data->player.plane_y = oldPlaneX * sin(rotSpeed) + data->player.plane_y * cos(rotSpeed);
	// }
	// else if (x > 480)
	// {
	// 	if (data->previous_dir > x)
	// 	{
	// 		data->player.dir_x = data->player.dir_x * cos(rotSpeed) - data->player.dir_y * sin(rotSpeed);
	// 		data->player.dir_y = oldDirX * sin(rotSpeed) + data->player.dir_y * cos(rotSpeed);
	// 		data->player.plane_x = data->player.plane_x * cos(rotSpeed) - data->player.plane_y * sin(rotSpeed);
	// 		data->player.plane_y = oldPlaneX * sin(rotSpeed) + data->player.plane_y * cos(rotSpeed);
	// 	}
	// 	data->player.dir_x = data->player.dir_x * cos(-rotSpeed) - data->player.dir_y * sin(-rotSpeed);
	// 	data->player.dir_y = oldDirX * sin(-rotSpeed) + data->player.dir_y * cos(-rotSpeed);
	// 	data->player.plane_x = data->player.plane_x * cos(-rotSpeed) - data->player.plane_y * sin(-rotSpeed);
	// 	data->player.plane_y = oldPlaneX * sin(-rotSpeed) + data->player.plane_y * cos(-rotSpeed);
	// }
	// data->previous_dir = x;
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
	// (void) y;
	// (void) x;
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

