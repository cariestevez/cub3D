/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:57:14 by hdorado-          #+#    #+#             */
/*   Updated: 2022/12/17 17:28:12 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

/*void	test(unsigned int i, char *c)
{
	i++;
	if(c[0] >= 'A' && c[0] <= 'Z')
		c[0] = c[0] + 32;
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}
/*
int	main(void)
{
	char	str[20];

	strcpy(str, "HellO WoRld!");
	puts(str);
	ft_striteri(str, test);
	puts(str);
}*/
