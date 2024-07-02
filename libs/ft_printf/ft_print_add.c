/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:40:18 by ahayon            #+#    #+#             */
/*   Updated: 2023/06/16 14:12:00 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i += write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		ft_print_char((int)str[i]);
		i += 1;
	}
	return (i);
}

int	ft_print_hexmaj(long n, int base)
{
	int		result;
	char	*sb;

	sb = "0123456789ABCDEF";
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		return (ft_print_hexmaj(n, base) + 1);
	}
	if (n < base)
		return (ft_print_char(sb[n]));
	else
	{
		result = ft_print_hexmaj(n / base, base);
		result += ft_print_hexmaj(n % base, base);
		return (result);
	}
}

int	ft_print_digit(long n, int base)
{
	int		result;
	char	*sb;

	sb = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		return (ft_print_digit(n, base) + 1);
	}
	if (n < base)
		return (ft_print_char(sb[n]));
	else
	{
		result = ft_print_digit(n / base, base);
		result += ft_print_digit(n % base, base);
		return (result);
	}
}
