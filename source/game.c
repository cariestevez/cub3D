/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <hdorado-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:49:09 by hdorado-          #+#    #+#             */
/*   Updated: 2024/03/19 17:32:38 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_fake_game(t_map *game)
{
	char	*arr[11];

	arr[0] = "1111111111";
	arr[1] = "1000000001";
	arr[2] = "1010000001";
	arr[3] = "1000001001";
	arr[4] = "1000000001";
	arr[5] = "1000N00001";
	arr[6] = "1000000001";
	arr[7] = "1000000001";
	arr[8] = "1000000001";
	arr[9] = "1111111111";
	arr[10] = 0;
	game->matrix = arr;
}

t_vector	ft_fill_vector(double x, double y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

void	ft_populate_player(t_player *player)
{
	player->pos = ft_fill_vector(4, 5);
	player->dir = ft_fill_vector(-1, 0);
	player->dir = ft_fill_vector(0, 0.66);
}

int	ft_initgame(void)
{
	t_map		*game;
	t_window	*window;
	t_player	*player;
	int	i;

	player = NULL;
	ft_fake_game(game);
	ft_populate_player(player);
	window->id = mlx_init(960, 600, "Walking simulator", true);
	window->w_id = mlx_new_image(window->id, 960, 600);
	mlx_loop(window->id);
	i = -1;
	while (++i < 960)
	{
		double cameraX = (2*i/959) - 1;
		//Keep adding raydirs
	}
}
