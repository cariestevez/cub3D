/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:49:09 by hdorado-          #+#    #+#             */
/*   Updated: 2024/04/03 17:56:53 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_raycast(void *param)
{
	double		i;
	t_map		*game;
	t_raycast	r;

	game = (t_map *) param;
	i = -1.0;
	render_floor_ceiling(game);
	while (++i < 960)
	{
		r.section = (2 * i / 959) - 1;
		ft_set_raycast(&r, game);
		ft_get_sidedist(&r, game);
		ft_find_wall(&r, game);
		if (r.walldist <= 0.001)
			r.lineheight = (int)(600 / 0.001);
		else
			r.lineheight = (int)(600 / r.walldist);
		r.drawstart = -r.lineheight / 2 + 600 / 2;
		r.drawend = r.lineheight / 2 + 600 / 2;
		if (r.drawstart < 0)
			r.drawstart = 0;
		if (r.drawend >= 600)
			r.drawend = 600 - 1;
		ft_draw(&r, game, (int) i);
	}
}

void	move_camera(t_map *game, char dir)
{
	double	angle;

	if (game->player->dir.y < 0 && game->player->dir.x >= 0)
		angle = acos(game->player->dir.x);
	else if (game->player->dir.y >= 0 && game->player->dir.x >= 0)
		angle = 2 * PI - acos(game->player->dir.x);
	else if (game->player->dir.y >= 0 && game->player->dir.x < 0)
		angle = 2 * PI - acos(game->player->dir.x);
	else
		angle = acos(game->player->dir.x);
	if (dir == 'L')
		angle += PI / 36;
	else if (dir == 'R')
		angle -= PI / 36;
	if (angle >= 2 * PI)
		angle -= 2 * PI;
	else if (angle < 0)
		angle += 2 * PI;
	game->player->dir.x = cos(angle);
	game->player->dir.y = -sin(angle);
	game->player->camera.x = cos(angle - PI / 2) * 0.66;
	game->player->camera.y = -sin(angle - PI / 2) * 0.66;
}

int	ft_wall_dist(t_map *game, t_vector tmp_pos)
{
	int	x;
	int	y;

	x = (int) tmp_pos.x;
	y = (int) tmp_pos.y;
	if (game->matrix[y][x] == '1')
		return (0);
	if (game->matrix[y + 1][x] == '1' && tmp_pos.y - y > 0.95)
		return (0);
	else if (game->matrix[y - 1][x] == '1' && tmp_pos.y - y < 0.05)
		return (0);
	else if (game->matrix[y][x + 1] == '1' && tmp_pos.x - x > 0.95)
		return (0);
	else if (game->matrix[y][x - 1] == '1' && tmp_pos.x - x < 0.05)
		return (0);
	return (1);
}

void	move_player(t_map *game, char dir)
{
	t_vector	tmp;

	if (dir == 'N')
		tmp = ft_fill_vector(game->player->pos.x + 0.2 * game->player->dir.x,
				game->player->pos.y + 0.2 * game->player->dir.y);
	else if (dir == 'S')
		tmp = ft_fill_vector(game->player->pos.x - 0.2 * game->player->dir.x,
				game->player->pos.y - 0.2 * game->player->dir.y);
	else if (dir == 'E')
		tmp = ft_fill_vector(game->player->pos.x - 0.2 * game->player->dir.y,
				game->player->pos.y + 0.2 * game->player->dir.x);
	else if (dir == 'W')
		tmp = ft_fill_vector(game->player->pos.x + 0.2 * game->player->dir.y,
				game->player->pos.y - 0.2 * game->player->dir.x);
	else
		tmp = ft_fill_vector(game->player->pos.x, game->player->pos.y);
	if (ft_wall_dist(game, tmp))
	{
		game->player->pos.x = tmp.x;
		game->player->pos.y = tmp.y;
	}
}

void	ft_my_keys(mlx_key_data_t keydata, void *param)
{
	t_map	*game;

	game = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->id);
		return ;
	}
	else if (keydata.key == MLX_KEY_LEFT)
		move_camera(game, 'L');
	else if (keydata.key == MLX_KEY_RIGHT)
		move_camera(game, 'R');
	else if (keydata.key == MLX_KEY_A)
		move_player(game, 'W');
	else if (keydata.key == MLX_KEY_S)
		move_player(game, 'S');
	else if (keydata.key == MLX_KEY_D)
		move_player(game, 'E');
	else if (keydata.key == MLX_KEY_W)
		move_player(game, 'N');
}
