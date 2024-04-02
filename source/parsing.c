/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:43:35 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/02 22:14:11 by cestevez         ###   ########.fr       */
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

int	save_textures(char **token, t_map *game)
{
	if (token && !token[0])
		return (0);
	if (token[2])
		return (printf("Error\nToo many words in line\n"), 1);
	if (!game->graphics->path_wall_n && ft_strncmp(token[0], "NO", 3) == 0)
		game->graphics->path_wall_n = ft_strdup(token[1]);
	else if (!game->graphics->path_wall_s && ft_strncmp(token[0], "SO", 3) == 0)
		game->graphics->path_wall_s = ft_strdup(token[1]);
	else if (!game->graphics->path_wall_e && ft_strncmp(token[0], "EA", 3) == 0)
		game->graphics->path_wall_e = ft_strdup(token[1]);
	else if (!game->graphics->path_wall_w && ft_strncmp(token[0], "WE", 3) == 0)
		game->graphics->path_wall_w = ft_strdup(token[1]);
	else if (parse_rgb(game, token))
		return (free_array(token), 1);
	return (free_array(token), 0);
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
		*line = trim_nl(line);
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

int	inspect_map(t_map *game, int i, int j, int *n_player)
{
	if (game->matrix[i][j] == 'N' || game->matrix[i][j] == 'S'
		|| game->matrix[i][j] == 'E' || game->matrix[i][j] == 'W')
	{
		ft_populate_player(game, i, j, game->matrix[i][j]);
		game->matrix[i][j] = '0';
		(*n_player)++;
	}
	else if (!(game->matrix[i][j] == '1' || game->matrix[i][j] == '0'
		|| game->matrix[i][j] == ' '))
		return (printf("Error\nInvalid char when map expected\n"), 1);
	return (0);
}

int	parse_map(int fd, t_map *game, char **line)
{
	while (ft_strlen(*line))
	{
		*line = trim_nl(line);
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
