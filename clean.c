/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:16:49 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/24 19:13:02 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void    free_tab(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return ;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void	close_game(t_data *data)
{
    if (data && data->map_line_bis)
        free(data->map_line_bis);
    if (data && data->mini_map.map)
        free_tab(data->mini_map.map);
    if (data->mlx_ptr)
	{
		if (data->mlx_win)
		{
			mlx_clear_window(data->mlx_ptr, data->mlx_win);
			mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		}
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}

int     close_window(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	data->mlx_win = NULL;
    return (0);
}
