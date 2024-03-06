/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:26:15 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/05 18:30:10 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_gnl_buff(int fd, char *line)
{
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return ;
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
	game->ceiling = 0;
	game->ground = 0;
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

int	check_args(int argc, char **argv)
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

int	pre_parsing_check(int fd, t_map *game)
{
	int		ret;
	char	*line;

	ret = 0;
	while (!game->ceiling || !game->ground || !game->txtr_wall_N ||
		!game->txtr_wall_S || !game->txtr_wall_E || !game->txtr_wall_W)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)//map is empty(read until the end with gnl??!)
			return (printf("Error\nMap is empty!\n"), 1);
		// if (ret == 0)//EOF reached
		// 	break ;
		if (ft_strlen(line) == 0)//empty line->gnl
			;
		else if (!save_data(line))//incorrect data in map(not saved)
			return (free_gnl_buff(line), 1);
	}
	free_gnl_buff(line);
	return (0);
	
	// if (ret == 0)
	// while (ret != 0)
	// {
    //     while (line == ' ')//skip empty lines at beginning
    //     {
    //         free(line);
	// 	    line = get_next_line(fd);
    //     }
    //     if ()
	// 	// if (invalid_char_in_map(line))
	// 	// 	return (free_gnl_buff(fd, line), 1);
	// 	free(line);
	// 	line = get_next_line(fd);
	// }
	// free(line);
	// return (0);
}

int check_map_format(char *map)
{
    int	fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nUnable to open the map file\n"), 1);
	if (pre_parsing_check(fd))
		return (close(fd), 1);
    return (close(fd), 0);
}

int	main(int argc, char **argv)
{
	t_map	*game;

	game = init_game();;
	if (!game)
		return (EXIT_FAILURE);
	if (check_args(argc, argv)
        || check_map(argv[1], game))
		return (EXIT_FAILURE);
	/*if (parse_and_validate(game, argv) == 1)
		return (EXIT_FAILURE);
	game->mlx = mlx_init(32 * game->width, 32 * game->height, "xoxo", true);
	if (!game->mlx)
		ft_mlxerror(game);
	create_images(game);
	display_images(game);
	mlx_key_hook(game->mlx, &my_keyhook, game);
	mlx_loop(game->mlx);*/
	return (free_success_exit(game));
}
