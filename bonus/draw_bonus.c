/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:55:06 by dvalino-          #+#    #+#             */
/*   Updated: 2024/08/06 19:16:45 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_ray_wall(t_data *data, t_ray_cast *ray)
{
	double	step_in_tex;
	double	tex_pos;

	ray->x = ray->draw_start - 1;
	if (!ray->side || ray->side == 2)
		ray->wall_x = data->player.pos_y
			+ ray->perp_walldist * data->player.ray_dir_y;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex.x = (int)(ray->wall_x * (double)TEX_HEIGHT);
	if ((!ray->side || ray->side == 2) && data->player.ray_dir_x > 0)
		ray->tex.x = TEX_HEIGHT - ray->tex.x;
	if ((ray->side == 1 || ray->side == 3) && data->player.ray_dir_y < 0)
		ray->tex.x = TEX_HEIGHT - ray->tex.x;
	step_in_tex = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (double)(ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* step_in_tex;
	while (++ray->x < ray->draw_end)
	{
		ray->tex.y = (int)(tex_pos) & (TEX_HEIGHT - 1);
		tex_pos += step_in_tex;
		ray->color = data->sprites.textures[ray->texnum][TEX_HEIGHT
			* ray->tex.y + ray->tex.x];
		my_mlx_pixel_put(&data->img, ray->y + (WIN_WIDTH / 2), ray->x,
			ray->color);
	}
}

void	init_draw_line(t_point a, t_point b, t_point *d, t_point *s)
{
	d->x = abs(a.x - b.x);
	d->y = abs(a.y - b.y);
	s->x = -1;
	s->y = -1;
	if (a.x < b.x)
		s->x = 1;
	if (a.y < b.y)
		s->y = 1;
}

void	draw_line(t_point a, t_point b, t_data *data)
{
	t_point	d;
	t_point	s;
	int		error;
	int		e2;

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

void	draw_square(int x, int y, int color, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->mini_map.block_h && i + x < WIN_HEIGHT)
	{
		j = 0;
		while (j < data->mini_map.block_w && j + y < WIN_WIDTH)
		{
			my_mlx_pixel_put(&data->img, j + y, i + x, color);
			j++;
		}
		i++;
	}
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
	while (i < WIN_HEIGHT / 2)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			my_mlx_pixel_put(&data->img, j, i, ceiling_color);
			my_mlx_pixel_put(&data->img, j++, (WIN_HEIGHT / 2) + i,
				floor_color);
		}
		i++;
	}
	return (0);
}
