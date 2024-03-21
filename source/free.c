/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:28:43 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/20 23:30:37 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_gnl_buff(int fd, char *line)
{
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

//images are freed by mlx_terminate in ft_terminate
void	free_graphics(t_graphics *graphic)
{
	free(graphic->path_wall_N);
	graphic->path_wall_N = NULL;
	free(graphic->path_wall_S);
	graphic->path_wall_S = NULL;
	free(graphic->path_wall_E);
	graphic->path_wall_E = NULL;
	free(graphic->path_wall_W);
	graphic->path_wall_W = NULL;
	free(graphic->txtr_wall_N);
	graphic->txtr_wall_N = NULL;
	free(graphic->txtr_wall_S);
	graphic->txtr_wall_S = NULL;
	free(graphic->txtr_wall_E);
	graphic->txtr_wall_E = NULL;
	free(graphic->txtr_wall_W);
	graphic->txtr_wall_W = NULL;
}

void	free_struct(t_map *game)
{
	free_graphics(game->graphics);
	free_array(game->matrix);
	free(game);
	game = NULL;
}

void	ft_terminate(t_map *game)
{
	free(game->player);
	game->player = NULL;
	free(game->w_id);
	game->w_id = NULL;
	mlx_terminate(game->id);
	game->id = NULL;
	free_struct(game);
}
