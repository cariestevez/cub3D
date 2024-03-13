/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:06:41 by hdorado-          #+#    #+#             */
/*   Updated: 2022/12/22 13:36:00 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdlib.h>
#include <stdio.h>*/
#include "libft.h"

static char	**ft_write_split(const char *s, int counter, char c, char **strar)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (counter >= j)
	{
		k = 0;
		while (s[i] == c)
			i++;
		while (i < (int)ft_strlen(s) && s[i] != c)
		{
			i++;
			k++;
		}
		strar[j] = ft_calloc(sizeof(char), (k + 1));
		if (!strar[j])
			return (0);
		ft_strlcpy(strar[j], s + i - k, k + 1);
		j++;
	}
	strar[j] = 0;
	return (strar);
}

static char	**ft_error_split(void)
{
	char	**strar;

	strar = ft_calloc(sizeof(char *), 1);
	if (!strar)
		return (0);
	strar[0] = 0;
	return (strar);
}

char	**ft_split(char const *s, char c)
{
	int		counter;
	int		i;
	char	**strar;

	i = 0;
	counter = 0;
	while (s[i] == c)
		i++;
	if (i >= (int)ft_strlen(s))
		return (ft_error_split());
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == c && s[i + 1] != c && (int)ft_strlen(s) > i + 1)
			counter++;
		i++;
	}
	strar = ft_calloc(sizeof(char *), (counter + 2));
	if (!strar)
		return (0);
	return (ft_write_split(s, counter, c, strar));
}
/*
int	main(void)
{
	char	**array;
	int	i;

	array = ft_split("Hello ultimate world!", 'l');
	i = 0;
	while(5 > i)
	{
		puts(array[i]);
		i++;
	}
}*/
