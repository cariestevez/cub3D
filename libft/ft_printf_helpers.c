/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:06:33 by hdorado-          #+#    #+#             */
/*   Updated: 2023/01/17 20:06:35 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr_recursive(unsigned int num)
{
	int	ret;

	ret = 0;
	if (num > 9)
		ret += ft_putnbr_recursive(num / 10);
	ret += ft_putchar(num % 10 + '0');
	return (ret);
}

int	ft_puthexa_recursive(unsigned long num, char c)
{
	int	ret;

	ret = 0;
	if (num > 15)
		ret += ft_puthexa_recursive(num / 16, c);
	num = num % 16;
	if (num < 10)
		ret += ft_putchar(num + '0');
	else if (c == 'x')
		ret += ft_putchar(num + 87);
	else
		ret += ft_putchar(num + 55);
	return (ret);
}

int	ft_putunint(unsigned int num)
{
	int	ret;

	ret = 0;
	if (num > 9)
		ret += ft_putnbr_recursive(num / 10);
	ret += ft_putchar(num % 10 + '0');
	return (ret);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
		i += ft_putchar(str[i]);
	return (i);
}
