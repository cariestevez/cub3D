/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:26:15 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/06 17:09:50 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_gnl_buff(int fd, char *line)
{
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] == NULL;
		i++
	}
}

t_map	*init_game(void)
{
	t_map *game;

	game = (t_map *)malloc(sizeof(t_map));
	if (!game)
		return (NULL);
	game->start_y = 0;
	game->start_x = 0;
	game->matrix = NULL;
    game->mlx = NULL;
	init_game_2(game);
	return (game);
}

void	init_game_2(t_map *game)
{
	game->ceiling = NULL;
	game->ground = NULL;
	game->txtr_wall_N = NULL;
    game->txtr_wall_S = NULL;
    game->txtr_wall_E = NULL;
    game->txtr_wall_W = NULL;

	game->img_wall_N = NULL;
    game->img_wall_S = NULL;
    game->img_wall_E = NULL;
    game->img_wall_W = NULL;

	return ;
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

int	save_rgb(t_map *game, char **token)//add check for correct RGB?
{
	if (ft_strncmp(token[0], "F", 2) == 0)
		game->floor = ft_strdup(token[1]);
	else if (ft_strncmp(token[0], "C", 2) == 0)
		game->ceiling = ft_strdup(token[1]);
	return (0);
}

int	save_textures(char *line, t_map *game)
{
	int	i;
	char **token;

	i = 0;
	token = ft_split(line, ' ');
	if (!token)
		return (1);
	while (token[i])//get array length
		i++;
	if (i != 2)
		return (1);
	if (ft_strncmp(token[0], "NO", 3) == 0)
		game->txtr_wall_N = ft_strdup(token[1]);
	else if (ft_strncmp(token[0], "SO", 3) == 0)
		game->txtr_wall_S = ft_strdup(token[1]);
	else if (ft_strncmp(token[0], "EA", 3) == 0)
		game->txtr_wall_E = ft_strdup(token[1]);
	else if (ft_strncmp(token[0], "WE", 3) == 0)
		game->txtr_wall_W = ft_strdup(token[1]);
	else if ((ft_strncmp(token[0], "F", 2) == 0
		|| ft_strncmp(token[0], "C", 2) == 0) && save_rgb(game, token))
		return (free_array(token), 1);
	else
		return (free_array(token), 1);
	return (free_array(token), 0);
}

int	parse_textures(int fd, t_map *game)
{
	int		ret;
	char	*line;

	ret = 0;
	line = NULL;
	while (!game->ceiling || !game->ground || !game->txtr_wall_N ||
		!game->txtr_wall_S || !game->txtr_wall_E || !game->txtr_wall_W)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)//map is empty(read until the end with gnl??!)entering only in 1st round?
			return (printf("Error\nMap is empty!\n"), 1);
		if (ft_strlen(line) == 0)//empty line->gnl
			;
		else if (ret == 0 || save_textures(line, game))//EOF reached(means no map on it!) or incorrect data in file(=>not saved)
			return (printf("Error\nInvalid file format\n"), free_gnl_buff(line) 1);
		free(line);
	}
	return (0);
}

int	is_closed(t_map *game)
{
	
}

//only 1, 0, N, S, E, W and space chars
//there must be 1 position coord(N, S, E, W)
	//there can just be 1 of them
//at least 3x3
//enclosed in walls (1's)
//no spaces inside of the walls (1's)
int	validate_map(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->matrix[i] != NULL)
	{
		while (game->matrix[i][j] != '\0')
		{
			if (!(game->matrix[i][j] == '1' || game->matrix[i][j] == '0' || game->matrix[i][j] == 'N'
				|| game->matrix[i][j] == 'S' || game->matrix[i][j] == 'E' || game->matrix[i][j] == 'W'
				|| game->matrix[i][j] == ' '))
				return (printf"Error\nInvalid character in map\n"), 1;
			j++;
		}
		i++;
	}
	if (i < 2 || j < 2)
		return (printf("Error\nMap too small\n"), 1);
	if (is_closed(game))
		return (printf("Error\nMap not enclosed in walls\n"), 1);
	return (0);
}

//num of rows unknown, increasing each time we enter this function = i (y coord) --> to be reallocated
//num of columns = length of map line = j (x coord)
//realloc
int	save_map_matrix[i](char *matrix[i], t_map *game)
{
	int	i;
	char **new_matrix;

	i = 0;
	new_matrix = NULL;
	while (game->matrix[i])//get array length
		i++;
	new_matrix = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_matrix)
		return (1);
	i = 0;
	while (game->matrix[i])
	{
		new_matrix[i] =	game->matrix[i];
		free(game->matrix[i]);
		game->matrix[i] = NULL;
		i++;
	}
	free(game->matrix);
	new_matrix[i] = ft_strdup(line);
	game->matrix = new_matrix;
}

//when we enter here there should just be empty lines or the map chars in the rest of the file from here
int	parse_map(int fd, t_map *game)
{
	int		ret;
	char	*line;

	line = NULL;
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ft_strlen(line) == 0 && game->matrix == NULL)//empty line->gnl
			;
		else if ((ret == 0 && game->matrix == NULL)
			|| (ft_strlen(line) == 0 && game->matrix != NULL)
			|| save_map_line(line, game))//EOF(=no map) or empty line in middle of map or error saving map
		{
			free_gnl_buff(line);
			return (printf("Error\nInvalid map format\n"), 1);
		}
		free(line);
		if (ret == 0)//EOF(nothing in buff to free)
			break ;
	}
	if (validate_map(game))
		return (1);
	return (0);
}

int parsing(char *map_file, t_map *game)
{
    int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nUnable to open the map file\n"), 1);
	if (parse_textures(fd, game) || parse_map(fd, game))
		return (close(fd), 1);
    return (close(fd), 0);
}

int	main(int argc, char **argv)
{
	t_map	*game;

	game = init_game();;
	if (!game)
		return (EXIT_FAILURE);
	if (args_check(argc, argv)
        || parsing(argv[1], game))
		return (free_struct(game), EXIT_FAILURE);
	/*if (parse_and_validate(game, argv) == 1)
		return (EXIT_FAILURE);
	game->mlx = mlx_init(32 * game->width, 32 * game->height, "xoxo", true);
	if (!game->mlx)
		ft_mlxerror(game);
	create_images(game);
	display_images(game);
	mlx_key_hook(game->mlx, &my_keyhook, game);
	mlx_loop(game->mlx);*/
	return (free_struct(game), EXIT_SUCCESS);
}
