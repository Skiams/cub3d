/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:31:51 by skiam             #+#    #+#             */
/*   Updated: 2024/07/25 15:21:39 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	ft_nstr(char const *s, char c)
{
    int i = 0;
    int n = 0;

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
    int i = 0;

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
    int nstr;
    int i;
    char **tab;

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
        int len = ft_strlenc(s, c);
        tab[i] = ft_substr(s, 0, len);
        if (!tab[i++])
            return (ft_free(tab));
        s += len;
    }
	return (tab);
}