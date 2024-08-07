/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:42 by ahayon            #+#    #+#             */
/*   Updated: 2024/08/07 13:11:36 by ahayon           ###   ########.fr       */
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
# include <sys/time.h>
# define WIN_WIDTH 960
# define WIN_HEIGHT 540
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define ZOOM_MINI 10

typedef enum e_code_texture
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING
}			t_code_texture;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_sprites
{
	t_img			img_north;
	t_img			img_south;
	t_img			img_west;
	t_img			img_east;
	int				*textures[4];
	int				floor[3];
	int				ceiling[3];
}	t_sprite;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_mini_map
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
	t_point	player_screen;
	t_point	player_pixel;
}			t_mini_map;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadis_x;
	double		deltadis_y;
}				t_player;

typedef struct s_ray_cast
{
	int				x;
	int				y;
	int				side;
	int				texnum;
	int				draw_start;
	int				draw_end;
	int				line_height;
	unsigned int	color;
	double			wall_x;
	double			camera_x;
	double			perp_walldist;
	t_point			tex;
	t_point			map;
	t_point			step;
}					t_ray_cast;

typedef struct s_game_key
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	key_w;
	int	key_s;
	int	key_a;
	int	key_d;
}		t_game_key;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	char		*map_line;
	char		*map_line_bis;
	char		player_char;
	int			p_nb;
	int			previous_dir;
	int			p_pos_x;
	int			p_pos_y;
	int			img_height;
	int			img_width;
	long long	time;
	long long	old_time;
	int			fd;
	int			index;
	int			map_height;
	int			is_in_door;
	t_game_key	game;
	t_player	player;
	t_mini_map	mini_map;
	t_img		img;
	t_sprite	sprites;
}				t_data;

// parsing
bool		check_format(char *str, int code);
char		*mini_gnl(int fd);
bool		parsing(char *argv, t_data *data);
bool		is_path_dir(char *path);
bool		check_validity(t_data *data);
bool		check_commas(char *str);
bool		parse_map(t_data *data, char **map);
bool		check_newline(char *str);
bool		texture_check(t_data *data, char *map, int **i);
bool		get_texture(t_data *data, char *map_line, int **i, int code);
bool		assign_texture(t_data *data, char *path, int code);
bool		assign_texture_bis(t_data *data, char *path, int code);
bool		check_edges(char **map);
bool		check_side(char **map, int *j, int *i);

// clean.c
int			close_window(t_data *data);
void		close_game(t_data *data);
void		free_tab(char **tab);
void		free_images(t_data *data);
int			get_last_line(char **map);

// execution.c
int			execution(t_data *data);

// render_window.c
int			render(t_data *data);
int			create_rgb(unsigned int r, unsigned int g, unsigned int b);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
long long	get_time(void);

// handle_player.c
int			handle_player(t_data *data);
void		set_player_pov(t_data *data);

// ray_casting.c
void		ray_casting(t_data *data);

// draw.c
void		draw_ray_wall(t_data *data, t_ray_cast *ray);
int			draw_background(t_data *data);

// player_movement.c
void		move_foward(t_data *data, double moveSpeed);
void		move_back(t_data *data, double moveSpeed);
void		move_left(t_data *data, double moveSpeed);
void		move_right(t_data *data, double moveSpeed);
void		player_rotation(t_game_key game, t_player *player, double rot_s);

// handle_keys.c
int			handle_keypress(int keysym, t_data *data);
int			handle_keyrelease(int keysym, t_data *data);
void		init_keys(t_data *data);

// utils
int			ft_atoi_cub(const char *nptr);
bool		check_tab(char **tab);
int			array_len(char **arr);
char		**ft_split_cub(char const *s, char c);

// execution_utils.c
int			max_min(int option, int a, int b);
int			array_len(char **arr);
int			acceptable_coordinates(int x, int y);
int			is_player(char c);
void		found_player_pos(t_data *data);
double		get_frame_time(t_data *data);

#endif