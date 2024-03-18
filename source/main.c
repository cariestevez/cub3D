/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <hdorado-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:26:15 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/18 14:54:46 by hdorado-         ###   ########.fr       */
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
		arr[i] = NULL;
		i++;
	}
}

int	free_struct(t_map *game)
{
	free(game->ceiling);
	free(game->ground);
	free(game->path_wall_N);
	free(game->path_wall_S);
	free(game->path_wall_E);
	free(game->path_wall_W);
	free(game->txtr_wall_N);
	free(game->txtr_wall_S);
	free(game->txtr_wall_E);
	free(game->txtr_wall_W);
	free(game->img_wall_N);
	free(game->img_wall_S);
	free(game->img_wall_E);
	free(game->img_wall_W);
	free_array(game->matrix);
	free(game->mlx);
	return (0);
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

	game->path_wall_N = NULL;
	game->path_wall_S = NULL;
	game->path_wall_E = NULL;
	game->path_wall_W = NULL;

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
	if (!game->ground && ft_strncmp(token[0], "F", 2) == 0)
		return (game->ground = ft_strdup(token[1]), 0);
	else if (!game->ceiling && ft_strncmp(token[0], "C", 2) == 0)
		return (game->ceiling = ft_strdup(token[1]), 0);
	return (1);
}

int	save_textures(char **token, t_map *game)
{
	int	i;

	i = 0;
	if (token[2])
		return (1);
	if (!game->path_wall_N && ft_strncmp(token[0], "NO", 3) == 0)
		game->path_wall_N = ft_strdup(token[1]);
	else if (!game->path_wall_S && ft_strncmp(token[0], "SO", 3) == 0)
		game->path_wall_S = ft_strdup(token[1]);
	else if (!game->path_wall_E && ft_strncmp(token[0], "EA", 3) == 0)
		game->path_wall_E = ft_strdup(token[1]);
	else if (!game->path_wall_W && ft_strncmp(token[0], "WE", 3) == 0)
		game->path_wall_W = ft_strdup(token[1]);
	else if ((ft_strncmp(token[0], "F", 2) == 0
		|| ft_strncmp(token[0], "C", 2) == 0) && save_rgb(game, token)) //Do we need the ft_strncmp? they are inside the save_rgb function. We could save the last else, since it would force to return 1 in case of a line that is not one of the 6 elements
		return (free_array(token), 1);
	else
		return (free_array(token), 1);
	return (free_array(token), 0);
}

int	parse_textures(int fd, t_map *game, char *line)
{
	char 	**token;

	token = NULL;
	line = get_next_line(fd);//1st call
	if (ft_strlen(line) == 0)
		return (printf("Error\nMap is empty!\n"), 1);
	while (ft_strlen(line) && (!game->ceiling || !game->ground || !game->txtr_wall_N ||
		!game->txtr_wall_S || !game->txtr_wall_E || !game->txtr_wall_W))//fill map metadata
	{
		line = ft_strtrim(line, "\n");
		if (ft_strlen(line) == 0)//empty line=> keep reading
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		token = ft_split(line, ' ');//if str is only spaces, it returns a ptr to an array with 1 empty token
		if (!token)//only if split fails allocating
			return (free_gnl_buff(fd, line), 1);
		if (token[0] && save_textures(token, game)) //If an empty line had spaces only, we filter it here
			return (printf("Error\nInvalid file format\n"), free_array(token), free_gnl_buff(fd, line), 1);
		free_array(token);
		token = NULL;
		free(line);
		line = get_next_line(fd);
	}
	if (ft_strlen(line) == 0)//arrived at EOF (=>textures and/or map are missing)
		return (printf("Error\nInvalid file format\n"), 1);
	return (0);
}

int	is_closed(t_map *game)
{
	int	i;
	int	j;

	i = -1;
	// Checks if the first line is only 1 or space. We can skip this I think, because the next logic would catch it nonetheless
	// while (game->matrix[0][++i])
	// {
	// 	if (game->matrix[0][j] != ' ' || game->matrix[0][j] != '1')
	// 		return (1);
	// }
	// i = 0;
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
				if ((!game->matrix[i - 1][j] || game->matrix[i - 1][j] == ' ')
					|| (!game->matrix[i + 1][j] || game->matrix[i + 1][j] == ' ')
					|| (!game->matrix[i][j + 1] || game->matrix[i][j + 1] == ' ')
					|| (!game->matrix[i][j - 1] || game->matrix[i][j - 1] == ' '))
						return (1);
			}
		}
	}
	return (0);
}

//only 1, 0, N, S, E, W and space chars
//there must be 1 position coord(N, S, E, W)
	//there can just be 1 of them
//at least 3x3
//enclosed in walls
//no spaces inside of the walls
int	validate_map(t_map *game)
{
	int	i;
	int	j;
	int	n_player;

	i = 0;
	n_player = 0;
	while (game->matrix[i] != NULL)
	{
		j = 0;
		while (game->matrix[i][j] != '\0')
		{
			if (game->matrix[i][j] == 'N' || game->matrix[i][j] == 'S'
				|| game->matrix[i][j] == 'E' || game->matrix[i][j] == 'W')
				n_player++;
			else if (!(game->matrix[i][j] == '1' || game->matrix[i][j] == '0' || game->matrix[i][j] == ' '))
				return (printf("Error\nInvalid character in map\n"), 1);
			j++;
		}
		i++;
		if (j < 2)
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

//num of rows unknown, increasing each time we enter this function = i (y coord) --> to be reallocated
//num of columns = length of map line = j (x coord)
int	save_map_line(char *line, t_map *game)
{
	int	i;
	char **new_matrix;

	i = 0;
	new_matrix = NULL;
	while (game->matrix[i])
		i++;
	new_matrix = (char **)ft_calloc(sizeof(char *) * (i + 1));
	if (!new_matrix)
		return (1);
	i = 0;
	while (game->matrix[i])
	{
		new_matrix[i] =	ft_strdup(game->matrix[i]);
		free(game->matrix[i]);
		game->matrix[i] = NULL;
		i++;
	}
	free(game->matrix);
	new_matrix[i] = ft_strdup(line);
	game->matrix = new_matrix;
	//free(new_matrix); If you free this here, you are deleting game->matrix too
	return (0);
}

//when we enter, from here there should just be empty lines or the map chars
int	parse_map(int fd, t_map *game, char *line)
{
	while (line)
	{
		if (ft_strlen(line) == 1 && game->matrix == NULL)//empty line(just '\n') before map =>keep reading
			;
		else if (((game->matrix == NULL) && ft_strchr(line))//what is this for? Isn't strchr missing a char?
			|| (ft_strlen(line) == 0 && game->matrix != NULL)
			|| save_map_line(line, game))//EOF(=no map) or empty line in middle of map or error saving map
		{
			free_gnl_buff(fd, line);
			return (printf("Error\nInvalid map format\n"), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (validate_map(game))
		return (1);
	return (0);
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
