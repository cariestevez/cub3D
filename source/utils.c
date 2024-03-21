/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:42:28 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/21 12:31:36 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_mlxerror(t_map *game)
{
	printf("%s\n", mlx_strerror(mlx_errno));
	free_struct(game);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (1);
	while (i < (int)ft_strlen(line))
	{
		if (ft_strncmp(&line[i], " ", 1) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	create_images(t_map *game, t_graphics *graphic)
{
	graphic->txtr_wall_N = mlx_load_png(graphic->path_wall_N);
	graphic->txtr_wall_S = mlx_load_png(graphic->path_wall_S);
	graphic->txtr_wall_E = mlx_load_png(graphic->path_wall_E);
	graphic->txtr_wall_W = mlx_load_png(graphic->path_wall_W);
	if (!graphic->txtr_wall_N || !graphic->txtr_wall_S
		|| !graphic->txtr_wall_E || !graphic->txtr_wall_W)
		return (1);
	printf("in create_images\n");
	graphic->img_wall_N = mlx_texture_to_image(game->id, graphic->txtr_wall_N);
	graphic->img_wall_S = mlx_texture_to_image(game->id, graphic->txtr_wall_S);
	graphic->img_wall_E = mlx_texture_to_image(game->id, graphic->txtr_wall_E);
	graphic->img_wall_W = mlx_texture_to_image(game->id, graphic->txtr_wall_W);
	if (!graphic->img_wall_N || !graphic->img_wall_S || !graphic->img_wall_E
		|| !graphic->img_wall_W)
		return (1);
	return (0);
}
