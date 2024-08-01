/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:25:03 by ahayon            #+#    #+#             */
/*   Updated: 2024/08/01 13:50:55 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_atoi_cub(const char *nptr)
{
	int	i;
	int	signe;
	int	res;

	i = 0;
	res = 0;
	signe = 1;
	if (nptr[i] < 48 || nptr[i] > 57)
		return (-1);
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] && (nptr[i] < 48 || nptr[i] > 57))
		return (-1);
	return (res * signe);
}

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
			return (NULL);
		}
		buffer[reads] = '\0';
		map = ft_strjoin(map, buffer);
	}
	return (map);
}

bool	check_format(char *str, int code)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (code == 1)
	{
		if ((str[i - 1] != 'b') || (str[i - 2] != 'u')
			|| (str[i - 3] != 'c') || (str[i - 4] != '.')
			|| (str[i - 5] == '/'))
			return (false);
	}
	else if (code == 2)
	{
		if ((str[i - 1] != 'm') || (str[i - 2] != 'p')
			|| (str[i - 3] != 'x') || (str[i - 4] != '.')
			|| str[i - 5] == '/')
			return (false);
	}
	return (true);
}

int	get_last_line(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
