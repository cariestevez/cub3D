/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:26:15 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/20 18:18:44 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_mlxerror(t_map *game)
{
	ft_printf("%s\n", mlx_strerror(mlx_errno));
	free_struct(game);
}

int	args_check(int argc, char **argv)
{
	size_t	len;

	len = 0;
	if (argc != 2)
	{
		ft_printf("Invalid arguments! Usage: %s <map_file.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	len = strlen(argv[1]);
	if (len < 4 || strcmp(argv[1] + len - 4, ".cub") != 0)
	{
		ft_printf("Invalid file extension! File must have .cub extension.\n");
		return (EXIT_FAILURE);
	}
	return (0);
}

int	convert_rgb(char **rgb_char, char c, t_map *game)
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
		game->ceiling = hex_color;
	else if (c == 'F')
		game->ground = hex_color;
	return (0);
}

int	validate_rgb(char c, char *raw_rgb, t_map *game)
{
	int i;
	char **rgb_char;

	i = 0;
	rgb_char = ft_split(raw_rgb, ',');
	if (!rgb_char)
		return (1);
	if ((rgb_char && rgb_char[3] != NULL)
		|| (!rgb_char[0] || !rgb_char[1] || !rgb_char[2]))
		return (printf("Error\nInvalid RGB format\n"), free_array(rgb_char), 1);
	if (c == 'F' && convert_rgb(rgb_char, c, game))
		return(free_array(rgb_char), 1);
	else if (c == 'C' && convert_rgb(rgb_char, c, game))
		return(free_array(rgb_char), 1);
	return (free_array(rgb_char), 0);
}

int	parse_rgb(t_map *game, char **token)
{
	if (!game->ground && ft_strncmp(token[0], "F", 2) == 0
		&& validate_rgb('F', token[1], game))
			return (1);
	else if (!game->ceiling && ft_strncmp(token[0], "C", 2) == 0
		&& validate_rgb('C', token[1], game))
			return (1);
	else if (!game->ground && !game->ceiling && ft_strncmp(token[0], "F", 2) && ft_strncmp(token[0], "C", 2))
		return (printf("Error\nInvalid file format\n"), 1);
	return (0);
}

int	save_textures(char **token, t_map *game)
{
	int	i;

	i = 0;
	if (token && !token[0])//to skip lines with only spaces
		return (0);
	if (token[2])
		return (printf("Error\nToo many words in line\n"), 1);
	if (!game->path_wall_N && ft_strncmp(token[0], "NO", 3) == 0)
		game->path_wall_N = ft_strdup(token[1]);
	else if (!game->path_wall_S && ft_strncmp(token[0], "SO", 3) == 0)
		game->path_wall_S = ft_strdup(token[1]);
	else if (!game->path_wall_E && ft_strncmp(token[0], "EA", 3) == 0)
		game->path_wall_E = ft_strdup(token[1]);
	else if (!game->path_wall_W && ft_strncmp(token[0], "WE", 3) == 0)
		game->path_wall_W = ft_strdup(token[1]);
	else if (parse_rgb(game, token))
		return (free_array(token), 1);
	return (free_array(token), 0);
}

int	parse_textures(int fd, t_map *game, char **line)
{
	char 	**token;

	token = NULL;
	*line = get_next_line(fd);
	if (ft_strlen(*line) == 0)
		return (printf("Error\nMap is empty!\n"), 1);
	while (ft_strlen(*line) && (!game->ceiling || !game->ground || !game->path_wall_N ||
		!game->path_wall_S || !game->path_wall_E || !game->path_wall_W))
	{
		*line = ft_strtrim(*line, "\n");
		if (ft_strlen(*line) == 0)
		{
			free(*line);
			*line = get_next_line(fd);
			continue ;
		}
		token = ft_split(*line, ' ');
		if (!token)
			return (free_gnl_buff(fd, *line), 1);
		if (save_textures(token, game))
			return (free_gnl_buff(fd, *line), 1);
		free(*line);
		*line = get_next_line(fd);
	}
	if (ft_strlen(*line) == 0)//arrived at EOF (=>textures and/or map are missing)-> I think this does nothing
		return (printf("Error\nInvalid file format\n"), 1);
	return (0);
}

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
			if (game->matrix[i][j] == '0' || game->matrix[i][j] == 'N'
				|| game->matrix[i][j] == 'S' || game->matrix[i][j] == 'W'
				|| game->matrix[i][j] == 'E') //If we find a 0 or player, and either of the "cross" positions doesn't exist or is space, the map is open
			{
				if ((!game->matrix[i - 1] || game->matrix[i - 1][j] == ' ')
					|| (!game->matrix[i + 1] || game->matrix[i + 1][j] == ' ')
					|| (!game->matrix[i][j + 1] || game->matrix[i][j + 1] == ' ')
					|| (!game->matrix[i][j - 1] || game->matrix[i][j - 1] == ' '))
					return (1);
			}
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
				n_player++;
			else if (!(game->matrix[i][j] == '1' || game->matrix[i][j] == '0' || game->matrix[i][j] == ' '))
				return (printf("Error\nInvalid character when map expected\n"), 1);
			j++;
		}
		i++;
		if (j < 2)//I love it but norminette doesn't
			break ;
	}
	if (i < 2 || j < 2)
		return (printf("Error\nMap too small\n"), 1);
	else if (n_player != 1)
		return (printf("Error\nWrong number of players\n"), 1);
	if (is_closed(game))
		return (printf("Error\nMap not enclosed in walls\n"), 1);
	return (0);
}

int	save_map_line(char *line, t_map *game)
{
	int	i;
	char **new_matrix;

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
		new_matrix[i] =	ft_strdup(game->matrix[i]);
		free(game->matrix[i]);
		game->matrix[i] = NULL;
		i++;
	}
	free(game->matrix);
	new_matrix[i] = ft_strdup(line);
	game->matrix = new_matrix;
	return (0);
}

int	is_empty_line(char *line)
{
	int i;

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
		else if (game->matrix != NULL && is_empty_line(*line))//should we send map to validate and ignore the rest of the file from here or return error bc of empty *line in the middle of the map?
		{
			free_gnl_buff(fd, *line);
			break ;
		}
		else if (save_map_line(*line, game))
			return (printf("Error\nError saving map\n"), free_gnl_buff(fd, *line), 1);
		free(*line);
		*line = get_next_line(fd);
	}
	return (validate_map(game));
}

int parsing(char *map_file, t_map *game)
{
	int	fd;
	char *line;

	line = NULL;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nUnable to open the map file\n"), 1);
	if (parse_textures(fd, game, &line) || parse_map(fd, game, &line))
		return (close(fd), 1);
	return (close(fd), 0);
}

int	create_images(t_map *game)
{
	game->txtr_wall_N = mlx_load_png(game->path_wall_N);
	game->txtr_wall_S = mlx_load_png(game->path_wall_S);
	game->txtr_wall_E = mlx_load_png(game->path_wall_E);
	game->txtr_wall_W = mlx_load_png(game->path_wall_W);
	if (!game->txtr_wall_N || !game->txtr_wall_S || !game->txtr_wall_E
		|| !game->txtr_wall_W)
		return (1);//(printf("Error\nFailure loading textures\n"), 1);
	game->img_wall_N = mlx_texture_to_image(game->mlx, game->txtr_wall_N);
	game->img_wall_S = mlx_texture_to_image(game->mlx, game->txtr_wall_S);
	game->img_wall_E = mlx_texture_to_image(game->mlx, game->txtr_wall_E);
	game->img_wall_W = mlx_texture_to_image(game->mlx, game->txtr_wall_W);
	if (!game->img_wall_N || !game->img_wall_S || !game->img_wall_E
		|| !game->img_wall_W)
		return (1);//(printf("Error\nFailure creating images\n"), 1);
	return (0);
}


int	main(int argc, char **argv)
{
	t_map	*game;

	game = init_struct();;
	if (!game)
		return (EXIT_FAILURE);
	if (args_check(argc, argv) || parsing(argv[1], game))
		return (free_struct(game), EXIT_FAILURE);
	if (create_images(game))
		return (free_struct(game), EXIT_FAILURE);
	ft_initgame();
	return (free_struct(game), EXIT_SUCCESS);
}
