/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <hdorado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:55:04 by hdorado-          #+#    #+#             */
/*   Updated: 2023/07/11 21:21:17 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_error(char **str, char **tmp)
{
	if (*str != NULL)
		free (*str);
	if (*tmp != NULL)
	{
		free (*tmp);
		*tmp = NULL;
	}
	return (NULL);
}

int	ft_search_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
