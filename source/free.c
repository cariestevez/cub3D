/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:28:43 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/02 21:38:13 by cestevez         ###   ########.fr       */
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
	free(graphic->path_wall_n);
	graphic->path_wall_n = NULL;
	free(graphic->path_wall_s);
	graphic->path_wall_s = NULL;
	free(graphic->path_wall_e);
	graphic->path_wall_e = NULL;
	free(graphic->path_wall_w);
	graphic->path_wall_w = NULL;
	mlx_delete_texture(graphic->txtr_wall_n);
	graphic->txtr_wall_n = NULL;
	mlx_delete_texture(graphic->txtr_wall_s);
	graphic->txtr_wall_s = NULL;
	mlx_delete_texture(graphic->txtr_wall_e);
	graphic->txtr_wall_e = NULL;
	mlx_delete_texture(graphic->txtr_wall_w);
	graphic->txtr_wall_w = NULL;
}

void	free_struct(t_map *game)
{
	free(game->player);
	game->player = NULL;
	free_graphics(game->graphics);
	free(game->graphics);
	game->graphics = NULL;
	free_array(game->matrix);
	free(game);
	game = NULL;
}

void	ft_mlxerror(t_map *game)
{
	printf("%s\n", mlx_strerror(mlx_errno));
	free_struct(game);
}
