/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:08:45 by ahayon            #+#    #+#             */
/*   Updated: 2023/05/16 15:49:34 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	p;
	size_t	i;
	char	*nstr;

	if (!s)
		return (NULL);
	p = ft_strlen(s);
	i = 0;
	nstr = (char *)malloc(sizeof(char) * p + 1);
	if (!nstr)
		return (NULL);
	while (i < p)
	{
		nstr[i] = f(i, s[i]);
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
