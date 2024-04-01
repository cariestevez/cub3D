/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <hdorado-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:42:28 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/01 15:54:32 by hdorado-         ###   ########.fr       */
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

t_vector	ft_fill_vector(double x, double y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

void	ft_populate_player(t_map *game, int x, int y, char dir)
{
	game->player = ft_calloc(sizeof(t_player), 1);
	game->player->pos = ft_fill_vector(y + 0.5, x + 0.5);
	if (dir == 'N')
	{
		game->player->dir = ft_fill_vector(0, -1);
		game->player->camera = ft_fill_vector(0.66, 0);
	}
	else if (dir == 'S')
	{
		game->player->dir = ft_fill_vector(0, 1);
		game->player->camera = ft_fill_vector(-0.66, 0);
	}
	else if (dir == 'W')
	{
		game->player->dir = ft_fill_vector(-1, 0);
		game->player->camera = ft_fill_vector(0, -0.66);
	}
	else if (dir == 'E')
	{
		game->player->dir = ft_fill_vector(1, 0);
		game->player->camera = ft_fill_vector(0, 0.66);
	}
}

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
// 	return (r << 24 | g << 16 | b << 8 | a);
// }

