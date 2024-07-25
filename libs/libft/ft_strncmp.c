/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:53:34 by ahayon            #+#    #+#             */
/*   Updated: 2023/05/23 11:49:03 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i]) && (s1[i] || s2[i]) && ((i + 1) < n))
	{
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

/*#include <stdio.h>

int	main()
{
	printf("%d\n", ft_strncmp("zblaha", "zblah", 8));
	printf("%d\n", ft_strncmp("tatc", "tctct", 3));
	printf("%d\n", ft_strncmp("undeux", "undeux", 6));
	printf("%d\n", ft_strncmp("zblih", "bulah", 2));
	printf("%d\n", ft_strncmp("zblih", "bulah", 0));
}*/
