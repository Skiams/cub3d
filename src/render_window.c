/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:18:36 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/25 17:18:37 by dvalino-         ###   ########.fr       */
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
