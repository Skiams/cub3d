/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:28:55 by ahayon            #+#    #+#             */
/*   Updated: 2023/05/24 12:47:12 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!len && (!little || !big))
		return (NULL);
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && *little && (i + j) < len)
		{
			if (j + 1 == ft_strlen(little))
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*int	main()
{
	const char tsais[] = "zblah zblah appa bula";
	const char tc[] = "appa";

	printf("%s\n", ft_strnstr(tsais, tc, 2));
	printf("%s\n", strnstr(tsais, tc, 2));
	return (0);
}*/
