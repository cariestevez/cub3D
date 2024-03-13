/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:55:19 by hdorado-          #+#    #+#             */
/*   Updated: 2022/12/20 20:08:30 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>*/
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		len;

	len = ft_strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str = ft_memmove(str, s, len);
	str[len] = '\0';
	return (str);
}
/*
int	main(void)
{
	char	*dest;
	char	str[20];

	strcpy(str, "Hello world!");
	puts(str);
	dest = ft_strdup(str);
	puts(dest);
}*/
