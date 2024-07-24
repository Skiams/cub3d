/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:49:43 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/23 19:07:10 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_values(t_data *data)
{
	int height;
	int width;
	int	i;

	i = 0;
	height = TEX_HEIGHT;
	width = TEX_WIDTH;
	data->img_height = &height;
	data->img_width = &width;
	while (i < 3)
	{
		data->sprites.floor[i] = -1;
		data->sprites.ceiling[i] = -1;
		i++;
	}
}

int	init(t_data *data)
{
	//data->mlx_ptr = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3d");
	if (data->mlx_win == NULL)
		return (printf("error window\n"), free(data->mlx_win), 0);
	data->img.img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	//map settings
	found_player_pos(data);
	init_keys(data);
	data->mini_map.nbr_columns = ft_strlen(data->mini_map.map[0]);
	data->mini_map.nbr_lines = array_len(data->mini_map.map);
	data->mini_map.block_height = (WINDOW_HEIGHT / 2) / ZOOM_MINI; // change later window_height for map_height
	data->mini_map.block_width = (WINDOW_WIDTH / 3) / ZOOM_MINI;
	data->mini_map.player_pixel.x = data->mini_map.block_height / 2;
	data->mini_map.player_pixel.y = data->mini_map.block_width / 2;
	return (1);
}

int	main(int argc, char **argv)
{
	static t_data	data = {0};
	
	// int height = TEX_HEIGHT;
	// int width = TEX_WIDTH;
	if (argc != 2)
		ft_printf("Error: Wrong argument\nPlease enter one .cub file as argument");
	// char *map[] = {
	// 	"11111111111111",
	// 	"10000000000011",
	// 	"1000000001001",
	// 	"100000N011111",
	// 	"100000001",
	// 	"11111000111111",
	// 	"10000000000001",
	// 	"11111111111111", NULL};
	// char **map2;
	// map2 = ft_calloc(sizeof(char*), array_len(map) + 1);
	// for (int i = 0; i < array_len(map); i++)
	// 	map2[i] = ft_strdup(map[i]);
	// data.mini_map.map = map2;

	// data.mlx_ptr = mlx_init();
	// if (data.mlx_ptr == NULL)
	// 	return (printf("mlx_init error\n"), 0);
	data.img_height = TEX_HEIGHT;
	data.img_width = TEX_WIDTH;
	if (!parsing(argv[1], &data))
		return (printf("problem parsing"), 1);
	// (void)argv;
	if (!init(&data))
		return (printf("init error\n"), 1);
	execution(&data);
	// data.sprites.img_north.addr = mlx_get_data_addr(data.sprites.img_north.img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	// printf("addr : %s\n", data.sprites.img_north.addr);
	// mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.sprites.img_north.img, 10, 10);
	mlx_destroy_image(data.mlx_ptr, data.img.img);
	mlx_destroy_display(data.mlx_ptr);
	// dprintf(2, "here\n");
	free(data.mlx_ptr);
	return (0);
}