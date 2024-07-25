/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:49:48 by ahayon            #+#    #+#             */
/*   Updated: 2023/10/16 14:46:54 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!c)
		return ((char *)s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
#include <string.h>
#include "ft_strlen.c"
int	main()
{
	const char s[] = "appa";
	
	printf("%s\n", ft_strchr(s, 0));
	printf("%s\n", strchr(s, 0));
	return (0);
(char *)s pointeur sur adresse memoire, donc pas de pb pour ajouter int)
}*/
