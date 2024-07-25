/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:42 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/25 20:13:52 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx/mlx.h"
# include "./libs/libft/libft.h"
# include "libs/ft_printf/ft_printf.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 540
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define ZOOM_MINI 10
# define MAX(a,b) (a > b) ? a : b
# define MIN(a,b) (a < b) ? a : b

typedef enum    e_code_texture
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    FLOOR,
    CEILING
}               t_code_texture;

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
	int				*textures[4];
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

typedef struct s_ray_cast
{
	int				x;
	int				y;
	int				side;
	int				texnum;
	int				drawStart;
	int				drawEnd;
	int				lineHeight;
	unsigned int	color;
	double			wallX;
	double			cameraX;
	double 			perpWallDist;
	t_point			tex;
	t_point			map;
	t_point 		step;
}					t_ray_cast;


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
	int	mouse;
}	t_game_key;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
    char    *map_line;
    char    *map_line_bis;
	char	player_char;
    int     p_nb;
	int		previous_dir;
    int     p_pos_x;
    int     p_pos_y;
	double	time;
	double	old_time;
    int     img_height;
    int     img_width;
	t_game_key	game;
	t_player	player;
	t_mini_map	mini_map;
	t_img		img;
	t_sprite	sprites;
}	t_data;

bool	check_format(char *str, int code);
char	*mini_gnl(int fd);
bool	parsing(char *argv, t_data *data);
bool	is_path_dir(char *path);
int     ft_atoi_cub(const char *nptr);
bool	check_tab(char **tab);
bool    check_validity(t_data *data);
bool	check_commas(char *str);
bool    parse_map(t_data *data, char **map);
char	**ft_split_cub(char const *s, char c);
bool	check_newline(char *str);
int	    execution(t_data *data);
void	found_player_pos(t_data *data);
void	init_keys(t_data *data);
int	    array_len(char **arr);
void    clean_exit(t_data *data);
int     close_window(t_data *data);
void	close_game(t_data *data);
bool	texture_check(t_data *data, char *map, int **i);
bool	get_texture(t_data *data, char *map_line, int **i, int code);
bool	assign_texture(t_data *data, char *path, int code);
bool	assign_texture_bis(t_data *data, char *path, int code);
bool	check_edges(char **map);

#endif