/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:42 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/26 18:31:16 by skiam            ###   ########.fr       */
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
# define WIN_WIDTH 960
# define WIN_HEIGHT 540
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define ZOOM_MINI 10

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
	int		block_w;
	int		block_h;
	t_point	p_pos;
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
}		t_game_key;

typedef struct	s_data
{
	void		*mlx_ptr;
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
    int			img_height;
    int			img_width;
	t_game_key	game;
	t_player	player;
	t_mini_map	mini_map;
	t_img		img;
	t_sprite	sprites;
}				t_data;

bool	check_format(char *str, int code);
char	*mini_gnl(int fd);
bool	parsing(char *argv, t_data *data);
bool	is_path_dir(char *path);
int		ft_atoi_cub(const char *nptr);
bool	check_tab(char **tab);
bool	check_validity(t_data *data);
bool	check_commas(char *str);
bool	parse_map(t_data *data, char **map);
char	**ft_split_cub(char const *s, char c);
bool	check_newline(char *str);
void	found_player_pos(t_data *data);
void	init_keys(t_data *data);
int		array_len(char **arr);
bool	texture_check(t_data *data, char *map, int **i);
bool	get_texture(t_data *data, char *map_line, int **i, int code);
bool	assign_texture(t_data *data, char *path, int code);
bool	assign_texture_bis(t_data *data, char *path, int code);
bool	check_edges(char **map);
bool	check_side(char **map, int *j, int *i);

// clean.c
int		close_window(t_data *data);
void	close_game(t_data *data);
void    free_tab(char **tab);

// execution.c
int		execution(t_data *data);

// render_window.c
int		render(t_data *data);
int		create_rgb(unsigned int r, unsigned int g, unsigned int b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// handle_player.c
int		handle_player(t_data *data);
void	set_player_pov(t_data *data);

// ray_casting.c
void	ray_casting(t_data *data);

// draw.c
void	draw_ray_wall(t_data *data, t_ray_cast *ray);
void	draw_line(t_point a, t_point b, t_data *data);
int		draw_background(t_data *data);
void	draw_square(int x, int y, int color, t_data *data);

// player_movement.c
void	move_foward(t_data *data, double moveSpeed);
void	move_back(t_data *data, double moveSpeed);
void	move_left(t_data *data, double moveSpeed);
void	move_right(t_data *data, double moveSpeed);
void	player_rotation(t_game_key game, t_player *player, double rot_speed);

// handle_keys.c
int		handle_keypress(int keysym, t_data *data);
int		handle_keyrelease(int keysym, t_data *data);
void	init_keys(t_data *data);

// minimap_bonus.c
void	draw_map(t_data *data);
void	draw_player(t_data *data);
void	change_player_pos(t_data *data);
void	calculate_map_arg(t_mini_map *mini_map);

// mouse_interaction_bonus.c
int		handle_mouse_movement(int x, int y, t_data *data);
int		leave_window(t_data *data);

// execution_utils.c
int		max_min(int option, int a, int b);
int		array_len(char **arr);
int		acceptable_coordinates(int x, int y);
int		is_player(char c);
void	found_player_pos(t_data *data);

#endif