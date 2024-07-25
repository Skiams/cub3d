/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:52:01 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/25 14:52:03 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	calculate_step_and_dist(t_data *data, t_ray_cast *ray)
{
	if (data->player.ray_dir_x < 0)
	{
		ray->step.x = -1;
		data->player.sideDist_x = (data->player.pos_x - ray->map.x)
			* data->player.deltaDis_x;
	}
	else
	{
		ray->step.x = 1;
		data->player.sideDist_x = (ray->map.x + 1.0 - data->player.pos_x)
			* data->player.deltaDis_x;
	}
	if (data->player.ray_dir_y < 0)
	{
		ray->step.y = -1;
		data->player.sideDist_y = (data->player.pos_y - ray->map.y)
			* data->player.deltaDis_y;
	}
	else
	{
		ray->step.y = 1;
		data->player.sideDist_y = (ray->map.y + 1.0 - data->player.pos_y)
			* data->player.deltaDis_y;
	}
}

void	choose_texture(t_ray_cast *ray)
{
	if (!ray->side && ray->step.x > 0)
		ray->texnum = 0;
	else if (!ray->side && ray->step.x < 0)
		ray->texnum = 1;
	else if (ray->side && ray->step.y > 0)
		ray->texnum = 2;
	else
		ray->texnum = 3;
}

void	calculate_ray_pos_and_dir(t_data *data, t_ray_cast *ray)
{
	ray->cameraX = 2 * ray->y / (double)(WIN_WIDTH - 1);
	if (data->player_char == 'W' || data->player_char == 'E')
		ray->cameraX *= -1;
	data->player.ray_dir_y = data->player.dir_y
		+ data->player.plane_y * ray->cameraX;
	data->player.ray_dir_x = data->player.dir_x
		+ data->player.plane_x * ray->cameraX;
	ray->map.x = (int)data->player.pos_x;
	ray->map.y = (int)data->player.pos_y;
	data->player.deltaDis_x = fabs(1 / data->player.ray_dir_x);
	data->player.deltaDis_y = fabs(1 / data->player.ray_dir_y);
}

void	ray_casting(t_data *data)
{
	t_ray_cast	ray;

	ray.y = -(WIN_WIDTH / 2) - 1;
	while (++ray.y < (WIN_WIDTH / 2))
	{
		calculate_ray_pos_and_dir(data, &ray);
		calculate_step_and_dist(data, &ray);
		ray.side = calculate_ray_hit(data, &ray);
		ray.perpWallDist = (data->player.sideDist_y - data->player.deltaDis_y);
		if (!ray.side)
			ray.perpWallDist
				= (data->player.sideDist_x - data->player.deltaDis_x);
		ray.lineHeight = (int)WIN_HEIGHT / ray.perpWallDist;
		ray.drawStart = -ray.lineHeight / 2 + WIN_HEIGHT / 2;
		if (ray.drawStart < 0)
			ray.drawStart = 0;
		ray.drawEnd = ray.lineHeight / 2 + WIN_HEIGHT / 2;
		if (ray.drawEnd > WIN_HEIGHT)
			ray.drawEnd = WIN_HEIGHT;
		choose_texture(&ray);
		ray.x = ray.drawStart - 1;
		ray.wallX = data->player.pos_x
			+ ray.perpWallDist * data->player.ray_dir_x;
		draw_ray_wall(data, &ray);
	}
}
