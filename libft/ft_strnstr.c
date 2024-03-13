/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:20:08 by hdorado-          #+#    #+#             */
/*   Updated: 2022/12/20 19:38:04 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	counter;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	j = ft_strlen(little);
	while (big[i] != '\0' && (i + j) <= len)
	{
		counter = 0;
		while (big[i + counter] == little[counter] && counter != j)
			counter++;
		if (counter == j)
			return ((char *)(big + i));
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	const char *big = "Foo Bar Baz";
	const char *little = "Bar";
	char	*ptr;

	ptr = ft_strnstr(big, little, 4);
	if (ptr != 0)
		printf("%s\n", ptr);
}*/
