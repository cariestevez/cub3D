/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado <hdorado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:10:58 by hdorado-          #+#    #+#             */
/*   Updated: 2023/07/10 22:16:28 by hdorado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line_bonus(int fd)
{
	static char	*tmp[4096];
	char		*buffer;
	char		*str;

	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	ft_bzero(str, (BUFFER_SIZE + 1));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str || !buffer)
		return (NULL);
	if (tmp[fd])
	{
		if (ft_search_nl(tmp[fd]) != -1)
		{
			ft_strlcpy(str, tmp[fd], ft_strlen(tmp[fd]) + 1);
			return (ft_return_line(buffer, str, &tmp[fd]));
		}
		str = ft_append(str, tmp[fd]);
		if (!str)
			return (NULL);
	}
	return (read_next_line(&buffer, &str, &tmp[fd], fd));
}

/*
int	main(void)
{
	char	*str;
	int	fd;
	
	fd = open("read_error.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("Result: %s\n", str);
	free (str);
	str = get_next_line(fd);
	printf("Result: %s\n", str);
	free (str);
	str = get_next_line(-1);
	printf("Result: %s\n", str);
	free (str);
	close(fd);
	fd = open("read_error.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("Result: %s\n", str);
	free (str);
	str = get_next_line(fd);
	printf("Result: %s\n", str);
	free (str);
	str = get_next_line(fd);
	printf("Result: %s\n", str);
	free (str);
}*/
