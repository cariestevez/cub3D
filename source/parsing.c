/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:43:35 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/01 19:05:12 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	parse_rgb(t_map *game, char **token)
{
	if (!game->graphics->ground && ft_strncmp(token[0], "F", 2) == 0
		&& validate_rgb('F', token[1], game))
		return (1);
	else if (!game->graphics->ceiling && ft_strncmp(token[0], "C", 2) == 0
		&& validate_rgb('C', token[1], game))
		return (1);
	else if (!game->graphics->ground && !game->graphics->ceiling
		&& ft_strncmp(token[0], "F", 2) && ft_strncmp(token[0], "C", 2))
		return (printf("Error\nInvalid file format\n"), 1);
	return (0);
}

int	parse_textures(int fd, t_map *game, char **line)
{
	char	**token;

	token = NULL;
	*line = get_next_line(fd);
	if (ft_strlen(*line) == 0)
		return (printf("Error\nFile is empty!\n"), 1);
	while (ft_strlen(*line) && (!game->graphics->ceiling
			|| !game->graphics->ground || !game->graphics->path_wall_n
			|| !game->graphics->path_wall_s || !game->graphics->path_wall_e
			|| !game->graphics->path_wall_w))
	{
		*line = ft_strtrim(*line, "\n");
		if (ft_strlen(*line) == 0)
		{
			ft_read(line, fd);
			continue ;
		}
		token = ft_split(*line, ' ');
		if (!token || save_textures(token, game))
			return (free_gnl_buff(fd, *line), 1);
		ft_read(line, fd);
	}
	if (ft_strlen(*line) == 0)
		return (printf("Error\nInvalid file format\n"), 1);
	return (0);
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

int	parse_map(int fd, t_map *game, char **line)
{
	while (ft_strlen(*line))
	{
		*line = ft_strtrim(*line, "\n");
		if (game->matrix == NULL && is_empty_line(*line))
		{
			free(*line);
			*line = get_next_line(fd);
			continue ;
		}
		else if (game->matrix != NULL && is_empty_line(*line))
		{
			free_gnl_buff(fd, *line);
			break ;
		}
		else if (save_map_line(*line, game))
			return (printf("Error saving map\n"), free_gnl_buff(fd, *line), 1);
		free(*line);
		*line = get_next_line(fd);
	}
	return (validate_map(game));
}

int	parsing(char *map_file, t_map *game)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nUnable to open the map file\n"), 1);
	if (parse_textures(fd, game, &line) || parse_map(fd, game, &line))
		return (close(fd), 1);
	return (close(fd), 0);
}
