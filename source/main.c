/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <hdorado-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:26:15 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/21 14:50:39 by hdorado-         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_map	*game;

	game = init_struct();
	if (!game)
		return (EXIT_FAILURE);
	if (args_check(argc, argv) || parsing(argv[1], game))
		return (free_struct(game), EXIT_FAILURE);
	//from here use ft_terminate to free
	game->id = mlx_init(960, 600, "xoxo", true);
	if (!game->id)
		return (ft_mlxerror(game), EXIT_FAILURE);
	printf("hello\n");
	if (create_images(game, game->graphics))
		return (free_struct(game), EXIT_FAILURE);
	ft_initgame(game);
	//mlx_close_window(game->id);
	return (ft_terminate(game), EXIT_SUCCESS);
}
