/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:23:25 by ahayon            #+#    #+#             */
/*   Updated: 2023/05/26 15:56:37 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_nstr(char const *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c)
			n++;
		while (s[i] != c && s[i])
			i++;
		if (s[i])
			i++;
	}
	return (n);
}

static int	ft_strlenc(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*ft_free(char **d)
{
	int	i;

	i = 0;
	while (d[i])
		free(d[i++]);
	free(d);
	return (0x0);
}

char	**ft_split(char const *s, char c)
{
	int		nstr;
	int		i;
	char	**d;

	if (!s)
		return (0x0);
	nstr = ft_nstr(s, c);
	d = malloc(sizeof(char *) * (nstr + 1));
	if (!d)
		return (0x0);
	d[nstr] = 0;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			d[i] = ft_substr(s, 0, ft_strlenc(s, c));
			if (!d[i++])
				return (ft_free(d));
			s += ft_strlenc(s, c);
		}
		else
			s++;
	}
	return (d);
}
/*#include <stdio.h>

int	main()
{
 	int i;
 	int j;
 	char c = ' ';
 	char const s[] = "  lorem ipsum dolor sit amet, consecteturs";
 	char **strsplit;

 	i = 0;
 	strsplit = ft_split(s, c);
 	while (strsplit[i])
 	{
 		j = 0;
 		while (strsplit[i][j])
		{
 			printf("%c", strsplit[i][j]);
 			j++;
 		}
 		printf("\n");
 		i++;
	}
}*/
