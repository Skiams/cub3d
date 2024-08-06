/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprites_bis_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:22:52 by dvalino-          #+#    #+#             */
/*   Updated: 2024/08/06 19:16:35 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	init_animation_tex(t_data *data)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		data->anim_sprite.textures_buffer[i]
			= (int *)mlx_get_data_addr(data->anim_sprite.tex[i].img,
				&data->anim_sprite.tex[i].bpp,
				&data->anim_sprite.tex[i].line_len,
				&data->anim_sprite.tex[i].endian);
		i++;
	}
}

void	get_animation_textures(t_data *data)
{
	const char	path[12][100] = {"textures/slide1.xpm", "textures/slide2.xpm",
		"textures/slide3.xpm", "textures/slide4.xpm",
		"textures/slide5.xpm", "textures/slide6.xpm",
		"textures/slide7.xpm", "textures/slide8.xpm",
		"textures/kirby1_1.xpm", "textures/kirby1_2.xpm",
		"textures/kirby2_1.xpm", "textures/kirby2_2.xpm"};
	int			i;

	i = 0;
	while (i < 12)
	{
		data->anim_sprite.tex[i].img = mlx_xpm_file_to_image(data->mlx_ptr,
				(char *)path[i], &(data->img_width), &(data->img_height));
		i++;
	}
	init_animation_tex(data);
}

void	draw_line_sprite(t_data *data, t_ray_cast *ray, double step_in_tex,
	double tex_pos)
{
	while (++ray->x < ray->draw_end)
	{
		ray->tex.y = (int)(tex_pos) & (TEX_HEIGHT - 1);
		tex_pos += step_in_tex;
		ray->color = data->anim_sprite.textures_buffer[data->anim_sprite.last]
		[TEX_HEIGHT * ray->tex.y + ray->tex.x];
		if ((ray->color & 0x00FFFFFF) != 0
			&& data->mini_map.map[ray->map.x][ray->map.y] != 'D'
			&& ray->map.x % 2 == 0)
			my_mlx_pixel_put(&data->img, ray->y + (WIN_WIDTH / 2), ray->x,
				ray->color);
	}
}

void	draw_ray_object(t_data *data, t_ray_cast *ray)
{
	double	step_in_tex;
	double	tex_pos;

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
	draw_line_sprite(data, ray, step_in_tex, tex_pos);
}
