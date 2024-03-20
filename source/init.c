/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:29:17 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/20 23:29:43 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_map	*init_struct(void)
{
	t_map	*game;

	game = (t_map *)ft_calloc(sizeof(t_map), 1);
	if (!game)
		return (NULL);
	game->matrix = NULL;
	init_graphics(game->graphics);
	game->player = NULL;
	game->w_id = NULL;
	game->id = NULL;
	return (game);
}

void	init_graphics(t_graphics *graphics)
{
	graphics->ceiling = 0;
	graphics->ground = 0;
	graphics->path_wall_N = NULL;
	graphics->path_wall_S = NULL;
	graphics->path_wall_E = NULL;
	graphics->path_wall_W = NULL;
	graphics->txtr_wall_N = NULL;
	graphics->txtr_wall_S = NULL;
	graphics->txtr_wall_E = NULL;
	graphics->txtr_wall_W = NULL;
	graphics->img_wall_N = NULL;
	graphics->img_wall_S = NULL;
	graphics->img_wall_E = NULL;
	graphics->img_wall_W = NULL;
}
