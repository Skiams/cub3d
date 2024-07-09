/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:42 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/09 17:58:39 by skiam            ###   ########.fr       */
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

typedef struct  s_data
{
    void    *mlx;
    void    *win;
    char    *map_line;
    char    **map;
    int     img_width;
    int     img_height;
    bool    player_count;
}   t_data;


void	check_format(char *str);
char	*mini_gnl(int fd);

#endif