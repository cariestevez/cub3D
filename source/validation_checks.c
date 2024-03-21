/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:46:17 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/21 17:06:58 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	is_closed(t_map *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->matrix[++i])
	{
		j = -1;
		while (game->matrix[i][++j])
		{
			while (game->matrix[i][j] == ' ')
				j++;
			if ((game->matrix[i][j] == '0' || game->matrix[i][j] == 'N'
				|| game->matrix[i][j] == 'S' || game->matrix[i][j] == 'W'
				|| game->matrix[i][j] == 'E') && (((!game->matrix[i - 1]
				|| game->matrix[i - 1][j] == ' ')
				|| (!game->matrix[i + 1] || game->matrix[i + 1][j] == ' ')
				|| (!game->matrix[i][j + 1] || game->matrix[i][j + 1] == ' ')
				|| (!game->matrix[i][j - 1] || game->matrix[i][j - 1] == ' '))))
				return (1);
		}
	}
	return (0);
}

int	validate_map(t_map *game)
{
	int	i;
	int	j;
	int	n_player;

	i = 0;
	n_player = 0;
	if (!game->matrix)
		return (printf("Error\nMissing map in file\n"), 1);
	while (game->matrix[i] != NULL)
	{
		j = 0;
		while (game->matrix[i][j] != '\0')
		{
			if (game->matrix[i][j] == 'N' || game->matrix[i][j] == 'S'
				|| game->matrix[i][j] == 'E' || game->matrix[i][j] == 'W')
			{
				//ft_populate_player(game);
				n_player++;
			}
			else if (!(game->matrix[i][j] == '1' || game->matrix[i][j] == '0'
				|| game->matrix[i][j] == ' '))
				return (printf("Error\nInvalid char when map expected\n"), 1);
			j++;
		}
		i++;
	}
	if (i < 2 || j < 2)
		return (printf("Error\nMap too small\n"), 1);
	else if (n_player != 1)
		return (printf("Error\nWrong number of players\n"), 1);
	if (is_closed(game))
		return (printf("Error\nMap not enclosed in walls\n"), 1);
	return (0);
}

int	save_textures(char **token, t_map *game)
{
	if (token && !token[0])
		return (0);
	if (token[2])
		return (printf("Error\nToo many words in line\n"), 1);
	if (!game->graphics->path_wall_N && ft_strncmp(token[0], "NO", 3) == 0)
		game->graphics->path_wall_N = ft_strdup(token[1]);
	else if (!game->graphics->path_wall_S && ft_strncmp(token[0], "SO", 3) == 0)
		game->graphics->path_wall_S = ft_strdup(token[1]);
	else if (!game->graphics->path_wall_E && ft_strncmp(token[0], "EA", 3) == 0)
		game->graphics->path_wall_E = ft_strdup(token[1]);
	else if (!game->graphics->path_wall_W && ft_strncmp(token[0], "WE", 3) == 0)
		game->graphics->path_wall_W = ft_strdup(token[1]);
	else if (parse_rgb(game, token))
		return (free_array(token), 1);
	return (free_array(token), 0);
}

int	save_rgb(char **rgb_char, char c, t_map *game)
{
	int				i;
	int				raw_color;
	unsigned long	hex_color;

	i = -1;
	raw_color = 0;
	hex_color = 0;
	while (rgb_char && rgb_char[++i])
	{
		raw_color = ft_atoi(rgb_char[i]);
		if (!(raw_color >= 0 && raw_color <= 255))
			return (printf("Error\nInvalid RGB color format\n"), 1);
		if (i == 0)
			hex_color += (raw_color & 0xff) << 16;
		else if (i == 1)
			hex_color += (raw_color & 0xff) << 8;
		else if (i == 2)
			hex_color += raw_color & 0xff;
	}
	if (c == 'C')
		game->graphics->ceiling = hex_color;
	else if (c == 'F')
		game->graphics->ground = hex_color;
	return (0);
}

int	validate_rgb(char c, char *raw_rgb, t_map *game)
{
	char	**rgb_char;

	rgb_char = ft_split(raw_rgb, ',');
	if (!rgb_char)
		return (1);
	if ((rgb_char && rgb_char[3] != NULL)
		|| (!rgb_char[0] || !rgb_char[1] || !rgb_char[2]))
		return (printf("Error\nInvalid RGB format\n"), free_array(rgb_char), 1);
	if (c == 'F' && save_rgb(rgb_char, c, game))
		return (free_array(rgb_char), 1);
	else if (c == 'C' && save_rgb(rgb_char, c, game))
		return (free_array(rgb_char), 1);
	return (free_array(rgb_char), 0);
}
