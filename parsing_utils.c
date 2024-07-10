/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:25:03 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/10 14:45:15 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_path_dir(char *path)
{
	int	fd;
	
	fd = open(path, 00200000);
	if (fd >= 0)
		return (close (fd), true);
	return (false);
}

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

bool	check_format(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if ((str[i - 1] != 'b') || (str[i - 2] != 'u')
	 || (str[i - 3] != 'c') || (str[i - 4] != '.'))
		return (false);
	else
		return (true);
}