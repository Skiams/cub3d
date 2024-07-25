/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:46:30 by ahayon            #+#    #+#             */
/*   Updated: 2023/05/30 12:49:13 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*d;

	i = 0;
	if (!s1 || !set)
		return (0x0);
	while (s1[i] && ft_isset(s1[i], set))
		i++;
	j = ft_strlen(s1) - 1;
	while (j > i && ft_isset(s1[j], set))
		j--;
	d = malloc(sizeof(char) * (j - i + 2));
	if (!d)
		return (0x0);
	k = 0;
	while (i <= j)
	{
		d[k] = s1[i];
		k++;
		i++;
	}
	d[k] = '\0';
	return (d);
}

/*#include <stdio.h>
#include "ft_strlen.c"

int	main()
{
	char const	d1[] = "qr";
	char const	set[] = "qr";

	printf("%s\n", ft_strtrim(d1, set));
	return (0);
}*/
