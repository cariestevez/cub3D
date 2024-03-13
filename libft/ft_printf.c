/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado <hdorado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:55:50 by hdorado-          #+#    #+#             */
/*   Updated: 2023/07/04 14:23:10 by hdorado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(unsigned long ptr)
{
	int	ret;

	ret = 0;
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	ret += write(1, "0x", 2);
	if (ptr > 15)
		ret += ft_puthexa_recursive(ptr / 16, 'x');
	ptr = ptr % 16;
	if (ptr < 10)
		ret += ft_putchar(ptr + '0');
	else
		ret += ft_putchar(ptr + 87);
	return (ret);
}

int	ft_puthexa(unsigned int num, char c)
{
	int	ret;

	ret = 0;
	if (num > 15)
		ret += ft_puthexa_recursive((unsigned long)num / 16, c);
	num = num % 16;
	if (num < 10)
		ret += ft_putchar(num + '0');
	else if (c == 'x')
		ret += ft_putchar(num + 87);
	else
		ret += ft_putchar(num + 55);
	return (ret);
}

int	ft_putnbr(int num)
{
	int	ret;

	ret = 0;
	if (num == -2147483648)
		return (write(1, "-2147483648", 11));
	if (num < 0)
	{
		ret += write(1, "-", 1);
		num = num * -1;
	}
	if (num > 9)
		ret += ft_putnbr_recursive((unsigned int)num / 10);
	ret += ft_putchar(num % 10 + '0');
	return (ret);
}

int	ft_eval_format(va_list *args, char c)
{
	if (c == 's')
		return (ft_putstr(va_arg((*args), char *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg((*args), int)));
	if (c == 'x' || c == 'X')
		return (ft_puthexa(va_arg((*args), unsigned int), c));
	if (c == 'p')
		return (ft_putptr(va_arg((*args), unsigned long)));
	if (c == 'c')
		return (ft_putchar(va_arg((*args), int)));
	if (c == 'u')
		return (ft_putunint(va_arg((*args), unsigned int)));
	if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		ret;
	int		i;
	va_list	args;

	ret = 0;
	i = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] != '%')
			ret += write(1, &str[i], 1);
		else
		{
			i++;
			ret += ft_eval_format(&args, str[i]);
		}
		i++;
	}
	va_end(args);
	return (ret);
}
