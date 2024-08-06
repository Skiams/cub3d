/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:06:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/08/01 14:22:28 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	ft_nstr(char const *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		n++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i] && s[i] == c)
			i++;
	}
	return (n);
}

static int	ft_strlenc(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		i++;
	return (i);
}

static void	*ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**ft_split_cub(char const *s, char c)
{
	int		nstr;
	int		i;
	char	**tab;
	int		len;

	if (!s)
		return (NULL);
	nstr = ft_nstr(s, c);
	tab = malloc(sizeof(char *) * (nstr + 1));
	if (!tab)
		return (NULL);
	tab[nstr] = (NULL);
	i = 0;
	while (*s)
	{
		len = ft_strlenc(s, c);
		tab[i] = ft_substr(s, 0, len);
		if (!tab[i++])
			return (ft_free(tab));
		s += len;
	}
	return (tab);
}
