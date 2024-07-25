/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_interaction_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:10:30 by dvalino-          #+#    #+#             */
/*   Updated: 2024/07/25 16:10:35 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_mouse_movement(int x, int y, t_data *data)
{
	(void)y;
	if (x < (WIN_WIDTH / 2) - 100)
		data->game.mouse = -1;
	else if (x > (WIN_WIDTH / 2) + 100)
		data->game.mouse = 1;
	else if (x == 0 || x == WIN_WIDTH)
		data->game.mouse = 0;
	else
		data->game.mouse = 0;
	return (0);
}

int	leave_window(t_data *data)
{
	data->game.mouse = 0;
	return (0);
}
