/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:29:17 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/01 17:42:44 by cestevez         ###   ########.fr       */
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
	game->graphics = init_graphics(game);
	game->player = NULL;
	game->w_id = NULL;
	game->id = NULL;
	return (game);
}

t_graphics	*init_graphics(t_map *g)
{
	g->graphics = (t_graphics *)calloc(sizeof(t_graphics), 1);
	if (!g->graphics)
		return (NULL);
	g->graphics->ceiling = 0;
	g->graphics->ground = 0;
	g->graphics->path_wall_N = NULL;
	g->graphics->path_wall_S = NULL;
	g->graphics->path_wall_E = NULL;
	g->graphics->path_wall_W = NULL;
	g->graphics->txtr_wall_N = NULL;
	g->graphics->txtr_wall_S = NULL;
	g->graphics->txtr_wall_E = NULL;
	g->graphics->txtr_wall_W = NULL;
	g->graphics->img_wall_N = NULL;
	g->graphics->img_wall_S = NULL;
	g->graphics->img_wall_E = NULL;
	g->graphics->img_wall_W = NULL;
	return (g->graphics);
}
