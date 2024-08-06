/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:49:43 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/30 17:00:42 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_values(t_data *data)
{
	int	height;
	int	width;
	int	i;

	i = 0;
	height = TEX_HEIGHT;
	width = TEX_WIDTH;
	data->img_height = height;
	data->img_width = width;
	while (i < 3)
	{
		data->sprites.floor[i] = -1;
		data->sprites.ceiling[i] = -1;
		i++;
	}
}

int	init(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, "cub3d");
	if (data->mlx_win == NULL)
		return (free(data->mlx_win), 0);
	data->img.img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	found_player_pos(data);
	init_keys(data);
	data->mini_map.nbr_columns = ft_strlen(data->mini_map.map[0]);
	data->mini_map.nbr_lines = array_len(data->mini_map.map);
	data->mini_map.block_h = (WIN_HEIGHT / 2) / ZOOM_MINI;
	data->mini_map.block_w = (WIN_WIDTH / 3) / ZOOM_MINI;
	data->mini_map.player_pixel.x = data->mini_map.block_h / 2;
	data->mini_map.player_pixel.y = data->mini_map.block_w / 2;
	return (1);
}

int	main(int argc, char **argv)
{
	static t_data	data = {0};

	if (argc != 2)
		return (ft_printf("Error: Wrong argument\nPlease use one .cub file"), 1);
	init_values(&data);
	if (!parsing(argv[1], &data))
		return (free_images(&data), close_game(&data), 1);
	if (!init(&data))
		return (ft_printf("Error\nInitialization failed\n"),
			close_game(&data), 1);
	execution(&data);
	close_game(&data);
	return (0);
}
	// mlx_destroy_image(data.mlx_ptr, data.img.img);
	// mlx_destroy_display(data.mlx_ptr);
	// free(data.mlx_ptr);
