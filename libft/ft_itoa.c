/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:53:41 by hdorado-          #+#    #+#             */
/*   Updated: 2022/12/22 13:35:06 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <stdlib.h>*/
#include "libft.h"

static char	*ft_itoa_write(char *str, int n, int len)
{
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n / 10 != 0)
	{
		str[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	str[len - 1] = n + 48;
	return (str);
}

static char	*ft_itoa_max(void)
{
	char	*str;

	str = ft_calloc(sizeof(char), 12);
	if (!str)
		return (0);
	ft_strlcpy(str, "-2147483648", 12);
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		copy;
	char	*str;

	len = 1;
	copy = n;
	if (n == -2147483648)
		return (ft_itoa_max());
	if (n < 0)
		len++;
	while (copy / 10 != 0)
	{
		len++;
		copy = copy / 10;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	return (ft_itoa_write(str, n, len));
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(10));
	printf("%s\n", ft_itoa(-10));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(176563));
	printf("%s\n", ft_itoa(-232545));
	printf("%s\n", ft_itoa(-0));
}*/
