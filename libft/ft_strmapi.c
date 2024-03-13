/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:31:09 by hdorado-          #+#    #+#             */
/*   Updated: 2022/12/20 20:29:51 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdlib.h>
#include <stdio.h>*/
#include "libft.h"
/*
char	test(unsigned int i, char c)
{
	i++;
	if(c >= 'A' && c <= 'Z')
		return(c + 32);
	return(c);
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i] = '\0';
	while (i)
	{
		str[i - 1] = (*f)(i - 1, s[i - 1]);
		i--;
	}
	return (str);
}
/*
int	main(void)
{
	char	*stri;

	stri = ft_strmapi("HelLo WoRlD!", test);
	puts(stri);
}*/
