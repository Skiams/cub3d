/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:52 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/18 17:18:17 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_EXEC_H
# define CUB_EXEC_H

# include "./cub3d.h"
# include <X11/X.h>
# include <math.h>
# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 540
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define ZOOM_MINI 10
# define MAX(a,b) (a > b) ? a : b
# define MIN(a,b) (a < b) ? a : b

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct	s_sprites
{
	t_img			img_north;
	t_img			img_south;
	t_img			img_west;
	t_img			img_east;
	unsigned int	textures[4][TEX_HEIGHT * TEX_WIDTH];
	int				floor[3];
	int				ceiling[3];
}	t_sprite;

typedef struct	s_point
{
	int	x;
	int	y;
}	t_point;

typedef	struct	s_mini_map
{
	int		show_map;
	char	**map;
	int		nbr_lines;
	int		nbr_columns;
	int		block_width;
	int		block_height;
	t_point	pos_player;
	t_point	start;
	t_point	end;
	t_point	playerScreen;
	t_point	player_pixel;
}			t_mini_map;

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		sideDist_x;
	double		sideDist_y;
	double		deltaDis_x;
	double		deltaDis_y;
}				t_player;

//Remember change the up, down, left, right with wsad
typedef struct	s_game_key
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	key_w;
	int	key_s;
	int	key_a;
	int	key_d;
}	t_game_key;


typedef struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	char	player_char;
	double	time;
	double	old_time;
	t_game_key	game;
	t_player	player;
	t_mini_map	mini_map;
	t_img		img;
	t_sprite	sprites;
}	t_data;

#endif
