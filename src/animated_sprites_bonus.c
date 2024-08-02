/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprites_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:32:49 by dvalino-          #+#    #+#             */
/*   Updated: 2024/08/02 18:12:52 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_animation_tex(t_data *data)
{
	data->anim_sprite.textures_buffer[0]
		= (int *)mlx_get_data_addr(data->anim_sprite.tex_1.img,
			&data->anim_sprite.tex_1.bpp,
			&data->anim_sprite.tex_1.line_len, &data->anim_sprite.tex_1.endian);
	data->anim_sprite.textures_buffer[1]
		= (int *)mlx_get_data_addr(data->anim_sprite.tex_2.img,
			&data->anim_sprite.tex_2.bpp,
			&data->anim_sprite.tex_2.line_len, &data->anim_sprite.tex_2.endian);
	data->anim_sprite.textures_buffer[2]
		= (int *)mlx_get_data_addr(data->anim_sprite.tex_3.img,
			&data->anim_sprite.tex_3.bpp,
			&data->anim_sprite.tex_3.line_len, &data->anim_sprite.tex_3.endian);
	data->anim_sprite.textures_buffer[3]
		= (int *)mlx_get_data_addr(data->anim_sprite.tex_4.img,
			&data->anim_sprite.tex_4.bpp,
			&data->anim_sprite.tex_4.line_len, &data->anim_sprite.tex_4.endian);
	data->anim_sprite.textures_buffer[4]
		= (int *)mlx_get_data_addr(data->anim_sprite.tex_5.img,
			&data->anim_sprite.tex_5.bpp,
			&data->anim_sprite.tex_5.line_len, &data->anim_sprite.tex_5.endian);
	data->anim_sprite.textures_buffer[5]
		= (int *)mlx_get_data_addr(data->anim_sprite.tex_6.img,
			&data->anim_sprite.tex_6.bpp,
			&data->anim_sprite.tex_6.line_len, &data->anim_sprite.tex_6.endian);
	data->anim_sprite.textures_buffer[6]
		= (int *)mlx_get_data_addr(data->anim_sprite.tex_7.img,
			&data->anim_sprite.tex_7.bpp,
			&data->anim_sprite.tex_7.line_len, &data->anim_sprite.tex_7.endian);
	data->anim_sprite.textures_buffer[7]
		= (int *)mlx_get_data_addr(data->anim_sprite.tex_8.img,
			&data->anim_sprite.tex_8.bpp,
			&data->anim_sprite.tex_8.line_len, &data->anim_sprite.tex_8.endian);
}

void	get_animation_textures(t_data *data)
{
	data->anim_sprite.tex_1.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide1.xpm", &(data->img_width), &(data->img_height));
	data->anim_sprite.tex_2.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide2.xpm", &(data->img_width), &(data->img_height));
	data->anim_sprite.tex_3.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide3.xpm", &(data->img_width), &(data->img_height));
	data->anim_sprite.tex_4.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide4.xpm", &(data->img_width), &(data->img_height));
	data->anim_sprite.tex_5.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide5.xpm", &(data->img_width), &(data->img_height));
	data->anim_sprite.tex_6.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide6.xpm", &(data->img_width), &(data->img_height));
	data->anim_sprite.tex_7.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide7.xpm", &(data->img_width), &(data->img_height));
	data->anim_sprite.tex_8.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide8.xpm", &(data->img_width), &(data->img_height));
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
		ray->color = data->anim_sprite.textures_buffer[data->anim_sprite.last][TEX_HEIGHT
			* ray->tex.y + ray->tex.x];
		if((ray->color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&data->img, ray->y + (WIN_WIDTH / 2), ray->x,
			ray->color);
	}
}

static void	choose_animated_texture(t_data *data)
{
	data->anim_sprite.time = get_time();
	// if (data->mini_map.show_map)
	// {
	// 	if (((data->anim_sprite.time - data->anim_sprite.old_time) > 3000))
	// 		data->anim_sprite.old_time = data->anim_sprite.time;
	// 	printf("ray->texnum : %d\n", ray->texnum);
	// 	data->anim_sprite.last = ray->texnum;
	// 	return ;
	// }
	data->anim_sprite.last = 0;
	if ((data->anim_sprite.time - data->anim_sprite.old_time) > 200)
		data->anim_sprite.last = 1;
	if ((data->anim_sprite.time - data->anim_sprite.old_time) > 400)
		data->anim_sprite.last = 2;
	if ((data->anim_sprite.time - data->anim_sprite.old_time) > 600) //
		data->anim_sprite.last = 3;
	if ((data->anim_sprite.time - data->anim_sprite.old_time) > 800)
		data->anim_sprite.last = 4;
	if ((data->anim_sprite.time - data->anim_sprite.old_time) > 1000)
		data->anim_sprite.last = 5;
	if ((data->anim_sprite.time - data->anim_sprite.old_time) > 1200) //
		data->anim_sprite.last = 6;
	if ((data->anim_sprite.time - data->anim_sprite.old_time) > 1400)
		data->anim_sprite.last = 7;
	if (((data->anim_sprite.time - data->anim_sprite.old_time) > 1600))
		data->anim_sprite.old_time = data->anim_sprite.time;
	printf("data->anim_sprite.last : %d\n", data->anim_sprite.last);
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
		if (data->mini_map.map[ray_cast->map.x][ray_cast->map.y] == 'D'
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
		choose_animated_texture(data);//, &ray);
		ray.x = ray.drawStart - 1;
		ray.wallX = data->player.pos_x
			+ ray.perpWallDist * data->player.ray_dir_x;
		draw_ray_object(data, &ray);
		data->anim_sprite.buffer[ray.y + (WIN_WIDTH / 2)] = ray.perpWallDist;
	}
}

// void	draw_ray_object(t_data *data)
// {
// 	t_point	draw;
// 	t_point tex;
// 	int		d;
// 	int		color;

// 	draw.x = data->anim_sprite.draw_start.x - 1;
// 		printf("draw.x : %d\n", draw.x);
// 	while (++draw.x < data->anim_sprite.draw_end.x)
// 	{
// 		tex.x = (int)(256 * (draw.x - (-data->anim_sprite.width_height.x / 2 + data->anim_sprite.sprite_screen.x))
// 			* TEX_WIDTH / data->anim_sprite.width_height.x) / 256;
// 		if (data->anim_sprite.transform_y > 0 && draw.x > 0 && draw.x < WIN_WIDTH
// 			&& data->anim_sprite.transform_y < data->anim_sprite.buffer[draw.x])
// 		{
// 			draw.y = data->anim_sprite.draw_start.y - 1;
// 			while (++draw.y < data->anim_sprite.draw_end.y)
// 			{
// 				d = (draw.y) * 256 - WIN_HEIGHT * 128 + data->anim_sprite.width_height.y * 128;
// 				tex.y = ((d * TEX_HEIGHT) / data->anim_sprite.width_height.y) / 256;
// 				color = data->anim_sprite.textures_buffer[data->anim_sprite.last][TEX_HEIGHT
// 					* tex.y + tex.x];
// 				if((color & 0x00FFFFFF) != 0)
// 					my_mlx_pixel_put(&data->img, draw.x, draw.y, color);
// 			}
// 		}
// 	}
// }

// void	swap(double *xp, double *yp)
// {
// 	double	temp;

// 	temp = *xp;
// 	*xp = *yp;
// 	*yp = temp;
// }

// void	sort_sprites(double *dist, int amount)
// {
// 	int	i;
// 	int	j;
// 	int	swapped;

// 	i = -1;
// 	swapped = 0;
// 	while (++i < amount - 1)
// 	{
// 		j = -1;
// 		while (++j < amount - i - 1)
// 		{
// 			if (dist[j] > dist[j + 1])
// 			{
// 				swap(&dist[j], &dist[j + 1]);
// 				swapped = 1;
// 			}
// 		}

// 	}
// }

// void	object_ray_casting(t_data *data)
// {
// 	int		i;

// 	i = -1;	
// 	while (++i < 1)
// 	{
// 		data->anim_sprite.sprite_x = (data->anim_sprite.pos_x - 0.5) - data->mini_map.p_pos.x;
// 		data->anim_sprite.sprite_y = (data->anim_sprite.pos_y - 0.5) - data->mini_map.p_pos.y;
// 		data->anim_sprite.inv_dev = 1.0 / (data->player.plane_x * data->player.dir_y - data->player.dir_x * data->player.plane_y);
// 		printf("data->anim_sprite.sprite_y  : %f\n", data->anim_sprite.sprite_y);
// 		data->anim_sprite.transform_x = data->anim_sprite.inv_dev
// 			* (data->player.dir_y * data->anim_sprite.sprite_x - data->player.dir_x * data->anim_sprite.sprite_y);
// 		data->anim_sprite.transform_y = data->anim_sprite.inv_dev
// 			* (-data->player.plane_y * data->anim_sprite.sprite_x + data->player.plane_x * data->anim_sprite.sprite_y);
// 		data->anim_sprite.sprite_screen.x = (int)((WIN_WIDTH / 2)
// 			* (1 + data->anim_sprite.transform_x / data->anim_sprite.transform_y));
// 		data->anim_sprite.width_height.y = abs((int)(WIN_HEIGHT / data->anim_sprite.transform_y));
// 		data->anim_sprite.draw_start.y = -data->anim_sprite.width_height.y / 2 + WIN_HEIGHT / 2;
// 		if (data->anim_sprite.draw_start.y < 0)
// 			data->anim_sprite.draw_start.y = 0;
// 		data->anim_sprite.draw_end.y = data->anim_sprite.width_height.y / 2 + WIN_HEIGHT / 2;
// 		if (data->anim_sprite.draw_end.y > WIN_HEIGHT)
// 			data->anim_sprite.draw_end.y = WIN_HEIGHT;

// 		data->anim_sprite.width_height.x = abs((int)(WIN_HEIGHT / data->anim_sprite.transform_y));
// 		data->anim_sprite.draw_start.x = -data->anim_sprite.width_height.x / 2 + data->anim_sprite.sprite_screen.x;
// 		if (data->anim_sprite.draw_start.x < 0)
// 			data->anim_sprite.draw_start.x = 0;
// 		data->anim_sprite.draw_end.x = data->anim_sprite.width_height.x / 2 + data->anim_sprite.sprite_screen.x;
// 		if (data->anim_sprite.draw_end.x > WIN_WIDTH)
// 			data->anim_sprite.draw_end.x = WIN_WIDTH;
// 		choose_animated_texture(data);
// 		draw_ray_object(data);
// 	}
// }

