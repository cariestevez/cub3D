/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:26:15 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/21 17:53:56 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3D.h"

// void	ft_display(t_map *game)
// {
// 	size_t	y;
// 	size_t	x;

// 	x = 0;
// 	y = 0;
// 	while (y < game->height)
// 	{
// 		x = -1;
// 		while (++x < game->width)
// 		{
// 			mlx_image_to_window(game->mlx, game->img_ground, x * 32, y * 32);
// 			if (game->matrix[y][x] == WALL)
// 				mlx_image_to_window(game->mlx, game->img_wall, x * 32, y * 32);
// 			if (game->matrix[y][x] == EXIT)
// 				mlx_image_to_window(game->mlx, game->img_exit, x * 32, y * 32);
// 			if (game->matrix[y][x] == COLLECT)
// 				mlx_image_to_window(game->mlx, game->img_item, x * 32, y * 32);
// 			if (game->matrix[y][x] == PLAYER)
// 				mlx_image_to_window(game->mlx, game->img_plyr, x * 32, y * 32);
// 		}
// 		y++;
// 	}
// }

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
	
	printf("in init game\n");
	game->id = mlx_init(WIN_WIDTH, WIN_HEIGHT, "xoxo", true);
	if (!game->id)
		return (ft_mlxerror(game), EXIT_FAILURE);
	//from here use ft_terminate to free
	if (create_images(game, game->graphics))
		return (ft_terminate(game), EXIT_FAILURE);
	printf("after create images\n");
	game->w_id = mlx_new_image(game->id, WIN_WIDTH, WIN_HEIGHT);
	// ft_raycast((void *) game);
	//render_floor_ceiling(game);
	mlx_image_to_window(game->id, game->w_id, 0, 0);
	//mlx_loop_hook(game->id, ft_raycast, game);
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
	if (ft_initgame(game))
		return (EXIT_FAILURE);
	//mlx_close_window(game->id);
	return (ft_terminate(game), EXIT_SUCCESS);
}
