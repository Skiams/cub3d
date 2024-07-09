/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:19:20 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/09 17:50:55 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*mini_gnl(int fd)
{
	char	*map;
	int		reads;
	char	buffer[1024];

	reads = 1;
	map = NULL;
	while (reads > 0)
	{
		reads = read(fd, buffer, 1024);
		if (reads == -1)
		{
			ft_printf("Error\nMap cannot be read\n");
			free(map);
			exit(1);
		}
		buffer[reads] = '\0';
		map = ft_strjoin(map, buffer);
	}
	return (map);
}

void	check_format(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'b')
		return (ft_printf("Error\nWrong map format\n"), exit(1));
	if (str[i - 2] != 'u')
		return (ft_printf("Error\nWrong map format\n"), exit(1));
	if (str[i - 3] != 'c')
		return (ft_printf("Error\nWrong map format\n"), exit(1));
	if (str[i - 4] != '.')
		return (ft_printf("Error\nWrong map format\n"), exit(1));
}
