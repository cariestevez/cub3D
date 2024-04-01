/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:29:17 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/01 19:01:41 by cestevez         ###   ########.fr       */
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
	g->graphics->path_wall_n = NULL;
	g->graphics->path_wall_s = NULL;
	g->graphics->path_wall_e = NULL;
	g->graphics->path_wall_w = NULL;
	g->graphics->txtr_wall_n = NULL;
	g->graphics->txtr_wall_s = NULL;
	g->graphics->txtr_wall_e = NULL;
	g->graphics->txtr_wall_w = NULL;
	g->graphics->img_wall_n = NULL;
	g->graphics->img_wall_s = NULL;
	g->graphics->img_wall_e = NULL;
	g->graphics->img_wall_w = NULL;
	return (g->graphics);
}
