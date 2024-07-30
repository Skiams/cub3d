/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:55:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/07/30 19:16:17 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_strlen2(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *buffer1, const char *stash)
{
	char	*res;
	size_t	i;
	size_t	j;
	char	*buffer;

	buffer = buffer1;
	i = -1;
	j = 0;
	if (!buffer)
	{
		buffer = malloc(1 * sizeof(char));
		buffer[0] = '\0';
	}
	if (!buffer || !stash)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen2(buffer) + ft_strlen(stash)) + 1);
	if (!res)
		return (NULL);
	while (buffer[++i] != '\0')
		res[i] = buffer[i];
	while (stash[j] != '\0')
		res[i++] = stash[j++];
	res[i] = '\0';
	free(buffer);
	return (res);
}
