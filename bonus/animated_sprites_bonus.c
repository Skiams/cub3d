/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprites_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:32:49 by dvalino-          #+#    #+#             */
/*   Updated: 2024/08/06 19:08:00 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	choose_animated_texture(t_data *data, t_ray_cast *ray)
{
	int	i;

	i = 0;
	data->anim_sprite.time = get_time();
	if (ray->map.y % 2 == 0)
	{
		data->anim_sprite.last = 0;
		while (i < 8)
		{
			if ((data->anim_sprite.time - data->anim_sprite.old_time) > i * 200)
				data->anim_sprite.last = i;
			i++;
		}
	}
	else
	{
		data->anim_sprite.last = 8;
		i = 8 - 1;
		while (++i < 12)
			if ((data->anim_sprite.time - data->anim_sprite.old_time)
				> (i - 8) * 200)
				data->anim_sprite.last = i;
	}
	if (((data->anim_sprite.time - data->anim_sprite.old_time) > 1600))
		data->anim_sprite.old_time = data->anim_sprite.time;
}

static int	calculate_ray_hit(t_data *data, t_ray_cast *ray)
{
	int	side;
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (data->player.sidedist_x < data->player.sidedist_y)
		{
			data->player.sidedist_x += data->player.deltadis_x;
			ray->map.x += ray->step.x;
			side = 0;
		}
		else
		{
			data->player.sidedist_y += data->player.deltadis_y;
			ray->map.y += ray->step.y;
			side = 1;
		}
		if (data->mini_map.map[ray->map.x][ray->map.y] == 'D'
			|| data->mini_map.map[ray->map.x][ray->map.y] == '1')
			hit = 1;
	}
	ray->perp_walldist = (data->player.sidedist_y - data->player.deltadis_y);
	return (side);
}

static void	calculate_step_and_dist(t_data *data, t_ray_cast *ray)
{
	if (data->player.ray_dir_x < 0)
	{
		ray->step.x = -1;
		data->player.sidedist_x = (data->player.pos_x - ray->map.x)
			* data->player.deltadis_x;
	}
	else
	{
		ray->step.x = 1;
		data->player.sidedist_x = (ray->map.x + 1.0 - data->player.pos_x)
			* data->player.deltadis_x;
	}
	if (data->player.ray_dir_y < 0)
	{
		ray->step.y = -1;
		data->player.sidedist_y = (data->player.pos_y - ray->map.y)
			* data->player.deltadis_y;
	}
	else
	{
		ray->step.y = 1;
		data->player.sidedist_y = (ray->map.y + 1.0 - data->player.pos_y)
			* data->player.deltadis_y;
	}
}

static void	calculate_ray_pos_and_dir(t_data *data, t_ray_cast *ray)
{
	ray->camera_x = 2 * ray->y / (double)(WIN_WIDTH - 1);
	if (data->player_char == 'W' || data->player_char == 'E')
		ray->camera_x *= -1;
	data->player.ray_dir_y = data->player.dir_y
		+ data->player.plane_y * ray->camera_x;
	data->player.ray_dir_x = data->player.dir_x
		+ data->player.plane_x * ray->camera_x;
	ray->map.x = (int)data->player.pos_x;
	ray->map.y = (int)data->player.pos_y;
	data->player.deltadis_x = fabs(1 / data->player.ray_dir_x);
	data->player.deltadis_y = fabs(1 / data->player.ray_dir_y);
}

void	animated_ray_casting(t_data *data)
{
	t_ray_cast	ray;

	ray.y = -(WIN_WIDTH / 2) - 1;
	ray.texnum = 0;
	while (++ray.y < (WIN_WIDTH / 2))
	{
		calculate_ray_pos_and_dir(data, &ray);
		calculate_step_and_dist(data, &ray);
		ray.side = calculate_ray_hit(data, &ray);
		if (!ray.side)
			ray.perp_walldist
				= (data->player.sidedist_x - data->player.deltadis_x);
		ray.line_height = (int)WIN_HEIGHT / ray.perp_walldist;
		ray.draw_start = -ray.line_height / 2 + WIN_HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + WIN_HEIGHT / 2;
		if (ray.draw_end > WIN_HEIGHT)
			ray.draw_end = WIN_HEIGHT;
		choose_animated_texture(data, &ray);
		ray.x = ray.draw_start - 1;
		ray.wall_x = data->player.pos_x
			+ ray.perp_walldist * data->player.ray_dir_x;
		draw_ray_object(data, &ray);
	}
}
/*
void	draw_ray_object(t_data *data)
{
	t_point	draw;
	t_point tex;
	int		d;
	int		color;
	draw.x = data->anim_sprite.draw_start.x - 1;
		printf("draw.x : %d\n", draw.x);
	while (++draw.x < data->anim_sprite.draw_end.x)
	{
		tex.x = (int)(256 * (draw.x - (-data->anim_sprite.width_height.x 
		/ 2 + data->anim_sprite.sprite_screen.x))
			* TEX_WIDTH / data->anim_sprite.width_height.x) / 256;
		if (data->anim_sprite.transform_y > 0
			&& draw.x > 0 && draw.x < WIN_WIDTH
			&& data->anim_sprite.transform_y < data->anim_sprite.buffer[draw.x])
		{
			draw.y = data->anim_sprite.draw_start.y - 1;
			while (++draw.y < data->anim_sprite.draw_end.y)
			{
				d = (draw.y) * 256 - WIN_HEIGHT
					* 128 + data->anim_sprite.width_height.y * 128;
				tex.y = ((d * TEX_HEIGHT)
					/ data->anim_sprite.width_height.y) / 256;
				color = data->anim_sprite.textures_buffer
					[data->anim_sprite.last][TEX_HEIGHT * tex.y + tex.x];
				if((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&data->img, draw.x, draw.y, color);
			}
		}
	}
}

void	swap(double *xp, double *yp)
{
	double	temp;

	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void	sort_sprites(double *dist, int amount)
{
	int	i;
	int	j;
	int	swapped;

	i = -1;
	swapped = 0;
	while (++i < amount - 1)
	{
		j = -1;
		while (++j < amount - i - 1)
		{
			if (dist[j] > dist[j + 1])
			{
				swap(&dist[j], &dist[j + 1]);
				swapped = 1;
			}
		}

	}
}

void	object_ray_casting(t_data *data)
{
	int		i;

	i = -1;	
	while (++i < 1)
	{
		data->anim_sprite.sprite_x = (data->anim_sprite.pos_x - 0.5)
			- data->mini_map.p_pos.x;
		data->anim_sprite.sprite_y
			= (data->anim_sprite.pos_y - 0.5) - data->mini_map.p_pos.y;
		data->anim_sprite.inv_dev = 1.0 / (data->player.plane_x
			* data->player.dir_y - data->player.dir_x * data->player.plane_y);
		printf("data->anim_sprite.sprite_y  : %f\n", data->anim_sprite.sprite_y);
		data->anim_sprite.transform_x = data->anim_sprite.inv_dev
			* (data->player.dir_y * data->anim_sprite.sprite_x
			- data->player.dir_x * data->anim_sprite.sprite_y);
		data->anim_sprite.transform_y = data->anim_sprite.inv_dev
			* (-data->player.plane_y * data->anim_sprite.sprite_x
			+ data->player.plane_x * data->anim_sprite.sprite_y);
		data->anim_sprite.sprite_screen.x = (int)((WIN_WIDTH / 2)
			* (1 + data->anim_sprite.transform_x
			/ data->anim_sprite.transform_y));
		data->anim_sprite.width_height.y = abs((int)(WIN_HEIGHT
			/ data->anim_sprite.transform_y));
		data->anim_sprite.draw_start.y = -data->anim_sprite.width_height.y
			/ 2 + WIN_HEIGHT / 2;
		if (data->anim_sprite.draw_start.y < 0)
			data->anim_sprite.draw_start.y = 0;
		data->anim_sprite.draw_end.y = data->anim_sprite.width_height.y
			/ 2 + WIN_HEIGHT / 2;
		if (data->anim_sprite.draw_end.y > WIN_HEIGHT)
			data->anim_sprite.draw_end.y = WIN_HEIGHT;
		data->anim_sprite.width_height.x = abs((int)(WIN_HEIGHT
			/ data->anim_sprite.transform_y));
		data->anim_sprite.draw_start.x = -data->anim_sprite.width_height.x
			/ 2 + data->anim_sprite.sprite_screen.x;
		if (data->anim_sprite.draw_start.x < 0)
			data->anim_sprite.draw_start.x = 0;
		data->anim_sprite.draw_end.x = data->anim_sprite.width_height.x
			/ 2 + data->anim_sprite.sprite_screen.x;
		if (data->anim_sprite.draw_end.x > WIN_WIDTH)
			data->anim_sprite.draw_end.x = WIN_WIDTH;
		choose_animated_texture(data);
		draw_ray_object(data);
	}
}
*/
