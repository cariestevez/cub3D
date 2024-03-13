/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <hdorado-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:39:11 by hdorado-          #+#    #+#             */
/*   Updated: 2023/07/18 22:15:12 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_useless_tmp(char **tmp)
{
	if (!(*tmp)[0])
	{
		free((*tmp));
		(*tmp) = NULL;
	}
}

char	*ft_return_line(char *buffer, char *str, char **tmp)
{
	int		i;
	char	*final_str;

	free(buffer);
	buffer = NULL;
	i = ft_search_nl(str);
	if (i == -1)
		i = (int) ft_strlen(str) - 1;
	final_str = malloc(sizeof(char) * (i + 2));
	if (!final_str)
		return (ft_error(NULL, tmp));
	ft_strlcpy(final_str, str, i + 2);
	free(*tmp);
	*tmp = malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!*tmp)
		return (ft_error(&final_str, NULL));
	ft_strlcpy(*tmp, str + i + 1, ft_strlen(str) - i);
	ft_useless_tmp(tmp);
	free(str);
	if (ft_strlen(final_str) == 0)
		return (ft_error(&final_str, tmp));
	return (final_str);
}

char	*ft_append(char *str, char *buffer)
{
	int		len;
	char	*str2;

	len = (int) ft_strlen(str);
	str2 = malloc(sizeof(char) * (len + ft_strlen(buffer) + 1));
	if (!str2)
		return (NULL);
	ft_strlcpy(str2, str, len + 1);
	ft_strlcpy(str2 + len, buffer, ft_strlen(buffer) + 1);
	free(str);
	return (str2);
}

char	*read_next_line(char **buffer, char **str, char **tmp, int fd)
{
	int	rd;

	while (1)
	{
		ft_bzero(*buffer, (BUFFER_SIZE + 1));
		rd = read(fd, *buffer, BUFFER_SIZE);
		if (rd < 0)
		{
			free(*str);
			if (*tmp)
			{
				free(*tmp);
				*tmp = NULL;
			}
			break ;
		}
		*str = ft_append(*str, *buffer);
		if (!*str)
			break ;
		if (ft_search_nl(*str) != -1 || rd < BUFFER_SIZE)
			return (ft_return_line(*buffer, *str, &*tmp));
	}
	free(*buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buffer;
	char		*str;

	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	ft_bzero(str, (BUFFER_SIZE + 1));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str || !buffer)
		return (NULL);
	if (tmp)
	{
		if (ft_search_nl(tmp) != -1)
		{
			ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
			return (ft_return_line(buffer, str, &tmp));
		}
		str = ft_append(str, tmp);
		if (!str)
			return (NULL);
	}
	return (read_next_line(&buffer, &str, &tmp, fd));
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
