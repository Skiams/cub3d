/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:42 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/10 18:20:51 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx/mlx.h"
# include "libs/libft/libft.h"
# include "libs/ft_printf/ft_printf.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef enum    e_code_texture
{
    NORTH,
    SOUTH,
    EAST,
    WEST
}               t_code_texture;

typedef struct  s_data
{
    int     tc;
    void    *mlx;
    void    *win;
    char    *map_line;
    char    **map;
    void    *img_north;
    void    *img_south;
    void    *img_east;
    void    *img_west;
    int     img_width;
    int     img_height;
    bool    player_count;
}   t_data;


bool	check_format(char *str, int code);
char	*mini_gnl(int fd);
bool	parsing(char *argv, t_data *data);
bool	is_path_dir(char *path);

#endif