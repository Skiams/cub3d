/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:16:49 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/24 10:46:10 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void    free_tab(char **tab)
{
    int i;
    int j;

    if (!tab)
        return ;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void    clean_exit(t_data *data)
{
    if (data && data->map_line_bis)
        free(data->map_line_bis);
    if (data && data->mini_map.map)
        free_tab(data->mini_map.map);
    if (data)
        free(data);
    exit (1);
}