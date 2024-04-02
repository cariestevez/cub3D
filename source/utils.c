/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:42:28 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/02 22:11:35 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*trim_nl(char **line)
{
	char	*copy;

	copy = ft_strtrim(*line, "\n");
	free(*line);
	return (copy);
}

void	ft_read(char **line, int fd)
{
	free(*line);
	*line = get_next_line(fd);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (1);
	while (i < (int)ft_strlen(line))
	{
		if (ft_strncmp(&line[i], " ", 1) != 0)
			return (0);
		i++;
	}
	return (1);
}

t_vector	ft_fill_vector(double x, double y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

int	save_map_line(char *line, t_map *game)
{
	int		i;
	char	**new_matrix;

	i = 0;
	new_matrix = NULL;
	printf("in save_map_line with line: %s\n", line);
	while (game->matrix && game->matrix[i])
		i++;
	new_matrix = (char **)ft_calloc(sizeof(char *), i + 2);
	if (!new_matrix)
		return (1);
	i = 0;
	while (game->matrix && game->matrix[i])
	{
		new_matrix[i] = ft_strdup(game->matrix[i]);
		free(game->matrix[i]);
		game->matrix[i] = NULL;
		i++;
	}
	free(game->matrix);
	new_matrix[i] = ft_strdup(line);
	game->matrix = new_matrix;
	return (0);
}
