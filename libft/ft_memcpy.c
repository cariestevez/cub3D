/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:44:03 by hdorado-          #+#    #+#             */
/*   Updated: 2022/12/17 16:56:17 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	i = 0;
	if (!d && !s)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
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

   ft_carina_memcpy(dest, str, 7);
   puts(dest);

   puts("With overlapping");
   strcpy(str,"This is string.h library function");
   puts(str);

   ft_carina_memcpy(str+2, str, 7);
   puts(str);
   
   return(0);
}
*/
