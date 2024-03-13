/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:44:03 by hdorado-          #+#    #+#             */
/*   Updated: 2022/12/17 17:00:37 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (s > d)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (s < d)
	{
		i = n;
		while (i != 0)
		{
			d[i -1] = s[i -1];
			i--;
		}
	}
	return (d);
}
/*
int main () {
   char str[50];
   char dest[50];
   puts("Without overlapping");
   strcpy(str,"This is string.h library function");
   strcpy(dest, "Esto es the destination");
   puts(str);
   puts(dest);

   ft_carina_memmove(dest, str, 7);
   puts(dest);

   puts("With overlapping src < dest");
   strcpy(str,"This is string.h library function");
   puts(str);

   ft_carina_memmove(str+2, str, 7);
   puts(str);
   
   puts("With overlapping dest < src");
   strcpy(str,"This is string.h library function");
   puts(str);

   ft_carina_memmove(str, str + 2, 7);
   puts(str);

   return(0);
}*/
