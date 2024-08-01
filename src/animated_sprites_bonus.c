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
	data->objects.textures_buffer[5]
		= (int *)mlx_get_data_addr(data->objects.tex_6.img,
			&data->objects.tex_6.bpp,
			&data->objects.tex_6.line_len, &data->objects.tex_6.endian);
	data->objects.textures_buffer[6]
		= (int *)mlx_get_data_addr(data->objects.tex_7.img,
			&data->objects.tex_7.bpp,
			&data->objects.tex_7.line_len, &data->objects.tex_7.endian);
	data->objects.textures_buffer[7]
		= (int *)mlx_get_data_addr(data->objects.tex_8.img,
			&data->objects.tex_8.bpp,
			&data->objects.tex_8.line_len, &data->objects.tex_8.endian);
}

void	get_animation_textures(t_data *data)
{
	data->objects.tex_1.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide1.xpm", &(data->img_width), &(data->img_height));
	data->objects.tex_2.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide2.xpm", &(data->img_width), &(data->img_height));
	data->objects.tex_3.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide3.xpm", &(data->img_width), &(data->img_height));
	data->objects.tex_4.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide4.xpm", &(data->img_width), &(data->img_height));
	data->objects.tex_5.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide5.xpm", &(data->img_width), &(data->img_height));
	data->objects.tex_6.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide6.xpm", &(data->img_width), &(data->img_height));
	data->objects.tex_7.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide7.xpm", &(data->img_width), &(data->img_height));
	data->objects.tex_8.img = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/slide8.xpm", &(data->img_width), &(data->img_height));
	init_animation_tex(data);
}

void	draw_ray_object(t_data *data)
{
	t_point	draw;
	t_point tex;
	int		d;
	int		color;

	draw.x = data->objects.draw_start.x - 1;
		printf("draw.x : %d\n", draw.x);
	while (++draw.x < data->objects.draw_end.x)
	{
		tex.x = (int)(256 * (draw.x - (-data->objects.width_height.x / 2 + data->objects.sprite_screen.x))
			* TEX_WIDTH / data->objects.width_height.x) / 256;
		if (data->objects.transform_y > 0 && draw.x > 0 && draw.x < WIN_WIDTH
			&& data->objects.transform_y < data->objects.buffer[draw.x])
		{
			draw.y = data->objects.draw_start.y - 1;
			while (++draw.y < data->objects.draw_end.y)
			{
				d = (draw.y) * 256 - WIN_HEIGHT * 128 + data->objects.width_height.y * 128;
				tex.y = ((d * TEX_HEIGHT) / data->objects.width_height.y) / 256;
				color = data->objects.textures_buffer[data->objects.last][TEX_HEIGHT
					* tex.y + tex.x];
				if((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&data->img, draw.x, draw.y, color);
			}
		}
	}
}

static void	choose_animated_texture(t_data *data)
{
	data->objects.time = get_time();
	// if (data->mini_map.show_map)
	// {
	// 	if (((data->objects.time - data->objects.old_time) > 3000))
	// 		data->objects.old_time = data->objects.time;
	// 	printf("ray->texnum : %d\n", ray->texnum);
	// 	data->objects.last = ray->texnum;
	// 	return ;
	// }
	data->objects.last = 0;
	if ((data->objects.time - data->objects.old_time) > 200)
		data->objects.last = 1;
	if ((data->objects.time - data->objects.old_time) > 400)
		data->objects.last = 2;
	if ((data->objects.time - data->objects.old_time) > 600) //
		data->objects.last = 3;
	if ((data->objects.time - data->objects.old_time) > 800)
		data->objects.last = 4;
	if ((data->objects.time - data->objects.old_time) > 1000)
		data->objects.last = 5;
	if ((data->objects.time - data->objects.old_time) > 1200) //
		data->objects.last = 6;
	if ((data->objects.time - data->objects.old_time) > 1400)
		data->objects.last = 7;
	if (((data->objects.time - data->objects.old_time) > 1600))
		data->objects.old_time = data->objects.time;
	printf("data->objects.last : %d\n", data->objects.last);
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
		data->objects.sprite_x = (data->objects.pos_x - 0.5) - data->mini_map.p_pos.x;
		data->objects.sprite_y = (data->objects.pos_y - 0.5) - data->mini_map.p_pos.y;
		data->objects.inv_dev = 1.0 / (data->player.plane_x * data->player.dir_y - data->player.dir_x * data->player.plane_y);
		printf("data->objects.inv_dev : %f\n", data->objects.inv_dev);
		data->objects.transform_x = data->objects.inv_dev
			* (data->player.dir_y * data->objects.sprite_x - data->player.dir_x * data->objects.sprite_y);
		data->objects.transform_y = data->objects.inv_dev
			* (-data->player.plane_y * data->objects.sprite_x + data->player.plane_x * data->objects.sprite_y);
		data->objects.sprite_screen.x = (int)((WIN_WIDTH / 2)
			* (1 + data->objects.transform_x / data->objects.transform_y));
		data->objects.width_height.y = abs((int)(WIN_HEIGHT / data->objects.transform_y));
		data->objects.draw_start.y = -data->objects.width_height.y / 2 + WIN_HEIGHT / 2;
		if (data->objects.draw_start.y < 0)
			data->objects.draw_start.y = 0;
		data->objects.draw_end.y = data->objects.width_height.y / 2 + WIN_HEIGHT / 2;
		if (data->objects.draw_end.y > WIN_HEIGHT)
			data->objects.draw_end.y = WIN_HEIGHT;

		data->objects.width_height.x = abs((int)(WIN_HEIGHT / data->objects.transform_y));
		data->objects.draw_start.x = -data->objects.width_height.x / 2 + data->objects.sprite_screen.x;
		if (data->objects.draw_start.x < 0)
			data->objects.draw_start.x = 0;
		data->objects.draw_end.x = data->objects.width_height.x / 2 + data->objects.sprite_screen.x;
		if (data->objects.draw_end.x > WIN_WIDTH)
			data->objects.draw_end.x = WIN_WIDTH;
		choose_animated_texture(data);
		draw_ray_object(data);
	}
}

