/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:01:22 by sojala            #+#    #+#             */
/*   Updated: 2024/11/29 13:21:29 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_format(const char *string, size_t i, va_list args)
{
	if (string[i] == 'c')
		return (ft_putchar((char) va_arg(args, int)));
	else if (string[i] == 'd' || string[i] == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (string[i] == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (string[i] == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (string[i] == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	else if (string[i] == 'x')
		return (ft_puthex_lower(va_arg(args, unsigned int)));
	else if (string[i] == 'X')
		return (ft_puthex_upper(va_arg(args, unsigned int)));
	else if (string[i] == '\0')
		return (-1);
	else
		return (ft_putchar('%'));
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		length;
	int		temp;

	i = 0;
	length = 0;
	if (!string)
		return (-1);
	va_start(args, string);
	while (string[i] && length != -1)
	{
		if (string[i] == '%')
			temp = ft_format(string, ++i, args);
		else
			temp = ft_putchar(string[i]);
		if (temp == -1)
			length = temp;
		else
			length += temp;
		i++;
	}
	va_end(args);
	return (length);
}
