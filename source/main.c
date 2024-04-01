/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:26:15 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/01 17:56:30 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

int	ft_initgame(t_map *game)
{
	printf("Here\n");
	game->id = mlx_init(WIN_WIDTH, WIN_HEIGHT, "xoxo", true);
	if (game->id == NULL)
		return (ft_mlxerror(game), EXIT_FAILURE);
	if (create_images(game, game->graphics))
		return (mlx_close_window(game->id), EXIT_FAILURE);
	game->w_id = mlx_new_image(game->id, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(game->id, game->w_id, 0, 0);
	mlx_key_hook(game->id, ft_my_keys, game);
	mlx_loop_hook(game->id, ft_raycast, game);
	mlx_loop(game->id);
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
	ft_initgame(game);
	return (ft_terminate(game), EXIT_SUCCESS);
}
