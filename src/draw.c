/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:55:06 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/25 14:55:09 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
