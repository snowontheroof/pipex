/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_pxxu.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:43:26 by sojala            #+#    #+#             */
/*   Updated: 2024/11/29 12:00:14 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putptr_hex(unsigned long n)
{
	int		len;
	int		mod;

	len = 0;
	mod = n % 16;
	if ((n / 16) > 0)
		len += ft_putptr_hex(n / 16);
	if (mod <= 9 && mod >= 0)
	{
		if (ft_putchar(mod + 48) == -1)
			return (-1);
		else
			len++;
	}
	else if (mod <= 15 && mod >= 10)
	{
		if (ft_putchar(mod + 87) == -1)
			return (-1);
		else
			len++;
	}
	return (len);
}

int	ft_putptr(void *ptr)
{
	int	len;
	int	temp;

	len = 0;
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	if (ft_putstr("0x") == -1)
		return (-1);
	else
		len = 2;
	temp = ft_putptr_hex((unsigned long) ptr);
	if (temp == -1)
		return (-1);
	else
		len += temp;
	return (len);
}

int	ft_puthex_lower(unsigned int n)
{
	int		len;
	int		mod;

	len = 0;
	mod = n % 16;
	if ((n / 16) > 0)
		len += ft_puthex_lower(n / 16);
	if (mod <= 9 && mod >= 0)
	{
		if (ft_putchar(mod + 48) == -1)
			return (-1);
		else
			len++;
	}
	else if (mod <= 15 && mod >= 10)
	{
		if (ft_putchar(mod + 87) == -1)
			return (-1);
		else
			len++;
	}
	return (len);
}

int	ft_puthex_upper(unsigned int n)
{
	int	len;
	int	mod;

	len = 0;
	mod = n % 16;
	if ((n / 16) > 0)
		len += ft_puthex_upper(n / 16);
	if (mod <= 9 && mod >= 0)
	{
		if (ft_putchar(mod + 48) == -1)
			return (-1);
		else
			len++;
	}
	else if (mod <= 15 && mod >= 10)
	{
		if (ft_putchar(mod + 55) == -1)
			return (-1);
		else
			len++;
	}
	return (len);
}

int	ft_putunsigned(unsigned int n)
{
	int		len;
	int		i;
	char	string[10];

	i = 0;
	len = 0;
	if (n == 0)
		return (write(1, "0", 1));
	while (n > 0)
	{
		string[i++] = (n % 10) + '0';
		n = n / 10;
	}
	len = i;
	while (i > 0)
	{
		if (write(1, &string[--i], 1) == -1)
			return (-1);
	}
	return (len);
}
