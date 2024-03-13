/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:37:44 by hdorado-          #+#    #+#             */
/*   Updated: 2022/12/22 13:35:32 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdlib.h>
#include <stdio.h>*/
#include "libft.h"
/*
size_t	ft_strlen(const char *s)
{
	size_t	i;
	
	i = 0;
	while(s[i] != '\0')
		i++;
	return(i);
}*/

static size_t	ft_get_i(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (set[j] != '\0')
	{
		if (s1[i] == set[j])
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*str;

	len = ft_strlen((char *)s1);
	i = ft_get_i(s1, set);
	j = 0;
	while (set[j] != '\0' && len != i)
	{
		if (s1[len - 1] == set[j])
		{
			j = 0;
			len--;
		}
		else
			j++;
	}
	str = ft_substr(s1, i, len - i);
	return (str);
}
/*
int	main(void)
{
	char	*strtrim;
	char s1[] = " lorem ipsum dolor sit amet";
    if (!(strtrim = ft_strtrim(s1, "l ")))
        puts("NULL");
    else
        puts(strtrim);
    if (strtrim == s1)
        puts("\nA new string was not returned");
}*/
