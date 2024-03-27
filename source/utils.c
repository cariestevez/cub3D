/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:42:28 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/25 23:59:10 by cestevez         ###   ########.fr       */
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

void	ft_populate_player(t_map *game, int x, int y, char c)
{
	game->player = ft_calloc(sizeof(t_player), 1);
	game->player->pos = ft_fill_vector(2, 8);//(x, y)
	//if (c == 'N') else if (c == 'S') else if (c == 'E') else
	game->player->dir = ft_fill_vector(0, -1);
	game->player->camera = ft_fill_vector(0.66, 0);
}

t_vector	ft_fill_vector(double x, double y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}
