/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:26:15 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/03 18:49:55 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_terminate(t_map *game)
{
	mlx_close_window(game->id);
	mlx_terminate(game->id);
	game->id = NULL;
	free_struct(game);
}

int	ft_initgame(t_map *game)
{
	game->id = mlx_init(WIN_WIDTH, WIN_HEIGHT, "xoxo", true);
	if (game->id == NULL)
		return (ft_mlxerror(game), EXIT_FAILURE);
	if (create_images(game, game->graphics))
		return (ft_terminate(game), EXIT_FAILURE);
	game->w_id = mlx_new_image(game->id, WIN_WIDTH + 20, WIN_HEIGHT + 20);
	if (!game->w_id)
		return (ft_terminate(game), EXIT_FAILURE);
	mlx_image_to_window(game->id, game->w_id, 0, 0);
	mlx_loop_hook(game->id, ft_raycast, game);
	mlx_key_hook(game->id, ft_my_keys, game);
	mlx_loop(game->id);
	return (ft_terminate(game), EXIT_SUCCESS);
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
	if (texture_exists(game->graphics))
		return (printf("Error\nInvalid texture path\n"), close(fd), 1);
	return (close(fd), 0);
}

int	args_check(int argc, char **argv)
{
	size_t	len;

	len = 0;
	if (argc != 2)
	{
		ft_printf("Error\nUsage: %s <map_file.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	len = strlen(argv[1]);
	if (len < 4 || strcmp(argv[1] + len - 4, ".cub") != 0)
	{
		ft_printf("Error\nFile must have .cub extension.\n");
		return (EXIT_FAILURE);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*game;

	game = init_struct();
	if (!game)
		return (EXIT_FAILURE);
	if (args_check(argc, argv) || parsing(argv[1], game))
		return (free_struct(game), EXIT_FAILURE);
	return (ft_initgame(game));
}
