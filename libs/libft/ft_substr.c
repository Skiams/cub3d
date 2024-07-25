/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:53:50 by ahayon            #+#    #+#             */
/*   Updated: 2023/05/26 15:53:58 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*subs;
	unsigned int	i;
	size_t			s_size;

	i = 0;
	if (!s)
		return (NULL);
	s_size = ft_strlen(s);
	if (start >= s_size)
		len = 0;
	if (len > s_size - start)
		len = s_size - start;
	subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (NULL);
	while (i < len)
	{
		subs[i] = s[start];
		start++;
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

/*
int	main()
{
	const char	*s;
	s = "Je suis une sorte de meuble";

	printf("%s\n", ft_substr(s, 3, 80));
}*/
