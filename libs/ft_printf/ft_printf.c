/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:27:05 by ahayon            #+#    #+#             */
/*   Updated: 2023/06/21 10:27:22 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_print_digipoint(unsigned long n)
{
	int		result;
	char	*sb;

	sb = "0123456789abcdef";
	if (n < 16)
		return (ft_print_char(sb[n]));
	else
	{
		result = ft_print_digipoint(n / 16);
		result += ft_print_digipoint(n % 16);
		return (result);
	}
}

int	ft_print_point(unsigned long nb)
{
	if (nb == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	else
	{
		write (1, "0x", 2);
		return (ft_print_digipoint(nb) + 2);
	}
}

int	ft_print_format(char c, va_list ap)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += ft_print_char(va_arg(ap, int));
	if (c == 'p')
		i += ft_print_point(va_arg(ap, unsigned long));
	if (c == 's')
		i += ft_print_str(va_arg(ap, char *));
	if (c == 'u')
		i += ft_print_digit((va_arg(ap, unsigned int)), 10);
	if (c == 'i' || c == 'd')
		i += ft_print_digit((va_arg(ap, int)), 10);
	if (c == 'x')
		i += ft_print_digit((va_arg(ap, unsigned int)), 16);
	if (c == 'X')
		i += ft_print_hexmaj((va_arg(ap, unsigned int)), 16);
	if (c == '%')
	{
		write (1, "%", 1);
		i += 1;
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	ap;

	va_start(ap, format);
	count = 0;
	if (!format)
		return (-1);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format += 1;
			count += ft_print_format(*format, ap);
		}
		else
			count += write(1, format, 1);
		format += 1;
	}
	va_end(ap);
	return (count);
}

/*
#include <stdio.h>
#include <limits.h>

int     main(void)
{
        int     count;
        char    str1[] = "tsais";
        int  i;
        long    x;
	char	*sb;

	sb = 0;
        x = 645;
        i = 4;

        printf("%i\n", ft_printf("%p tsais\n", sb));
        printf("i%\n", printf("%p tsais\n", sb));
}*/
