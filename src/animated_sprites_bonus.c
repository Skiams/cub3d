/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprites_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:32:49 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/31 16:32:52 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	change_object_animation(t_data *data)
// {
// 	long long	current_time;
// 	long long	diff;

// 	current_time = get_time();
// 	diff = current_time - data->objects.old_time;

// 	if (diff > 1000)
// 		data->objects.old_time = current_time;
// }

void	init_animation_tex(t_data *data)
{
	data->objects.textures_buffer[0]
		= (int *)mlx_get_data_addr(data->objects.tex_1.img,
			&data->objects.tex_1.bpp,
			&data->objects.tex_1.line_len, &data->objects.tex_1.endian);
	data->objects.textures_buffer[1]
		= (int *)mlx_get_data_addr(data->objects.tex_2.img,
			&data->objects.tex_2.bpp,
			&data->objects.tex_2.line_len, &data->objects.tex_2.endian);
	data->objects.textures_buffer[2]
		= (int *)mlx_get_data_addr(data->objects.tex_3.img,
			&data->objects.tex_3.bpp,
			&data->objects.tex_3.line_len, &data->objects.tex_3.endian);
	data->objects.textures_buffer[3]
		= (int *)mlx_get_data_addr(data->objects.tex_4.img,
			&data->objects.tex_4.bpp,
			&data->objects.tex_4.line_len, &data->objects.tex_4.endian);
	data->objects.textures_buffer[4]
		= (int *)mlx_get_data_addr(data->objects.tex_5.img,
			&data->objects.tex_5.bpp,
			&data->objects.tex_5.line_len, &data->objects.tex_5.endian);
}

void	get_animation_textures(t_data *data)
{
	data->objects.tex_1.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/texture_animation/coin1.xpm", &(data->img_width), &(data->img_height));
	data->objects.tex_2.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/texture_animation/coin2.xpm", &(data->img_width), &(data->img_height));
	data->objects.tex_3.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/texture_animation/coin3.xpm", &(data->img_width), &(data->img_height));
	data->objects.tex_4.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/texture_animation/coin4.xpm", &(data->img_width), &(data->img_height));
	data->objects.tex_5.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/texture_animation/coin6.xpm", &(data->img_width), &(data->img_height));		
	init_animation_tex(data);
}

void	draw_ray_object(t_data *data, t_ray_cast *ray)
{
	double	step_in_tex;
	double	tex_pos;

	if (!ray->side)
		ray->wallX = data->player.pos_y
			+ ray->perpWallDist * data->player.ray_dir_y;
	ray->wallX -= floor(ray->wallX);
	ray->tex.x = (int)(ray->wallX * (double)TEX_HEIGHT);
	if (!ray->side && data->player.ray_dir_x > 0)
		ray->tex.x = TEX_HEIGHT - ray->tex.x;
	if (ray->side && data->player.ray_dir_y < 0)
		ray->tex.x = TEX_HEIGHT - ray->tex.x;
	step_in_tex = 1.0 * TEX_HEIGHT / ray->lineHeight;
	tex_pos = (double)(ray->drawStart - WIN_HEIGHT / 2 + ray->lineHeight / 2)
		* step_in_tex;
	while (++ray->x < ray->drawEnd)
	{
		ray->tex.y = (int)(tex_pos) & (TEX_HEIGHT - 1);
		tex_pos += step_in_tex;
		ray->color = data->objects.textures_buffer[ray->texnum][TEX_HEIGHT
			* ray->tex.y + ray->tex.x];
		if((ray->color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&data->img, ray->y + (WIN_WIDTH / 2), ray->x,
			ray->color);
	}
}

static int	calculate_ray_hit(t_data *data, t_ray_cast *ray_cast)
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
		if (data->mini_map.map[ray_cast->map.x][ray_cast->map.y] == '2'
			|| data->mini_map.map[ray_cast->map.x][ray_cast->map.y] == '1')
		{
			hit = 1;
		}
	}
	return (side);
}

static void	calculate_step_and_dist(t_data *data, t_ray_cast *ray)
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

static void	choose_animated_texture(t_data *data, t_ray_cast *ray)
{
	data->objects.time = get_time();
	ray->texnum = 0;
	if ((data->objects.time - data->objects.old_time) > 500)
		ray->texnum = 1;
	if ((data->objects.time - data->objects.old_time) > 1000)
		ray->texnum = 2;
	if ((data->objects.time - data->objects.old_time) > 1500)
		ray->texnum = 3;
	if ((data->objects.time - data->objects.old_time) > 2000)
		ray->texnum = 4;
	if (((data->objects.time - data->objects.old_time) > 2500))
		data->objects.old_time = data->objects.time;
	printf("ray->texnum : %d\n", ray->texnum);
}

static void	calculate_ray_pos_and_dir(t_data *data, t_ray_cast *ray)
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

void	object_ray_casting(t_data *data)
{
	t_ray_cast	ray;

	ray.y = -(WIN_WIDTH / 2) - 1;
	ray.texnum = 0;
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
		choose_animated_texture(data, &ray);
		ray.x = ray.drawStart - 1;
		ray.wallX = data->player.pos_x
			+ ray.perpWallDist * data->player.ray_dir_x;
		draw_ray_object(data, &ray);
		data->objects.buffer[ray.y + (WIN_WIDTH / 2)] = ray.perpWallDist;
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
