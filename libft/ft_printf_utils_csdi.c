/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_csdi.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojala <sojala@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:53:00 by sojala            #+#    #+#             */
/*   Updated: 2024/11/29 12:04:50 by sojala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_write(int n, int neg)
{
	int		i;
	int		len;
	char	string[11];

	i = 0;
	while (n > 0)
	{
		string[i++] = (n % 10) + '0';
		n = n / 10;
	}
	if (neg == 1)
		string[i++] = '-';
	len = i;
	while (i > 0)
	{
		if (write(1, &string[--i], 1) == -1)
			return (-1);
	}
	return (len);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	else
		return (write(1, s, ft_strlen(s)));
}

int	ft_putnbr(int n)
{
	int		i;
	int		neg;

	i = 0;
	neg = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n == 0)
		return (write(1, "0", 1));
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	return (ft_putnbr_write(n, neg));
}
