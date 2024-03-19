#include "../include/cub3D.h"

t_map	*init_game(void)
{
	t_map *game;

	game = (t_map *)ft_calloc(sizeof(t_map), 1);
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