/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <hdorado-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:49:09 by hdorado-          #+#    #+#             */
/*   Updated: 2024/04/01 19:04:57 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

uint32_t	ft_get_pixel(mlx_image_t *image, double horizontal, double vertical)
{
	int			x;
	int			y;
	uint32_t	color;

	color = 0;
	if (horizontal >= 0)
		x = (int)(95 * horizontal);
	else
		x = (int)(95 * (1.0 + horizontal));
	y = (int)(95 * vertical);
	color += image->pixels[(y * 96 + x) * 4] << 24;
	color += image->pixels[(y * 96 + x) * 4 + 1] << 16;
	color += image->pixels[(y * 96 + x) * 4 + 2] << 8;
	color += image->pixels[(y * 96 + x) * 4 + 3];
	return (color);
}

typedef struct s_raycast
{
	t_vector	ray;
	t_vector	d_dist;
	t_vector	s_dist;
	double		section;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		walldist;
	int			lineheight;
	int			drawstart;
	int			drawend;
}	t_raycast;

void	ft_raycast(void *param)
{
	double		i;
	t_map		*game;
	t_raycast	r;
	uint32_t	hex_color;
	int			j;

	game = (t_map *) param;
	i = -1.0;
	render_floor_ceiling(game);
	while (++i < 960)
	{
		r.section = (2 * i / 959) - 1;
		r.ray.x = game->player->dir.x + game->player->camera.x * r.section;
		r.ray.y = game->player->dir.y + game->player->camera.y * r.section;
		r.mapx = (int)game->player->pos.x;
		r.mapy = (int)game->player->pos.y;
		if (r.ray.x == 0)
			r.d_dist.x = fabs(1 / 1e-30);
		else
			r.d_dist.x = fabs(1 / r.ray.x);
		if (r.ray.y == 0)
			r.d_dist.y = fabs(1 / 1e-30);
		else
			r.d_dist.y = fabs(1 / r.ray.y);
		if (r.ray.x < 0)
		{
			r.stepx = -1;
			r.s_dist.x = (game->player->pos.x - r.mapx) * r.d_dist.x;
		}
		else
		{
			r.stepx = 1;
			r.s_dist.x = (r.mapx + 1.0 - game->player->pos.x) * r.d_dist.x;
		}
		if (r.ray.y < 0)
		{
			r.stepy = -1;
			r.s_dist.y = (game->player->pos.y - r.mapy) * r.d_dist.y;
		}
		else
		{
			r.stepy = 1;
			r.s_dist.y = (r.mapy + 1.0 - game->player->pos.y) * r.d_dist.y;
		}
		r.hit = 0;
		while (!r.hit)
		{
			if (r.s_dist.x < r.s_dist.y)
			{
				r.s_dist.x += r.d_dist.x;
				r.mapx += r.stepx;
				r.side = 0;
			}
			else
			{
				r.s_dist.y += r.d_dist.y;
				r.mapy += r.stepy;
				r.side = 1;
			}
			if (game->matrix[r.mapy][r.mapx] == '1')
				r.hit = 1;
		}
		if (r.side == 0)
			r.walldist = (r.s_dist.x - r.d_dist.x);
		else
			r.walldist = (r.s_dist.y - r.d_dist.y);
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
		j = r.drawstart;
		while (j <= r.drawend)
		{
			if (r.side && (int) r.mapy < (int) game->player->pos.y)
			{
				hex_color = ft_get_pixel(game->graphics->img_wall_n, (r.ray.x * r.walldist + game->player->pos.x - ((int)(r.ray.x * r.walldist + game->player->pos.x))), ((double)(((r.lineheight - 600) / 2) + j)) / ((double)(r.lineheight)));
				mlx_put_pixel(game->w_id, (int) i, j, hex_color);
			}
			else if (r.side && (int) r.mapy > (int) game->player->pos.y)
			{
				hex_color = ft_get_pixel(game->graphics->img_wall_s, (r.ray.x * r.walldist + game->player->pos.x - ((int)(r.ray.x * r.walldist + game->player->pos.x))), ((double)(((r.lineheight - 600) / 2) + j)) / ((double)(r.lineheight)));
				mlx_put_pixel(game->w_id, (int) i, j, hex_color);
			}
			else if (!r.side && (int) r.mapx > (int) game->player->pos.x)
			{
				hex_color = ft_get_pixel(game->graphics->img_wall_e, (r.ray.y * r.walldist + game->player->pos.y - ((int)(r.ray.y * r.walldist + game->player->pos.y))), ((double)(((r.lineheight - 600) / 2) + j)) / ((double)(r.lineheight)));
				mlx_put_pixel(game->w_id, (int) i, j, hex_color);
			}
			else
			{
				hex_color = ft_get_pixel(game->graphics->img_wall_w, (r.ray.y * r.walldist + game->player->pos.y - ((int)(r.ray.y * r.walldist + game->player->pos.y))), ((double)(((r.lineheight - 600) / 2) + j)) / ((double)(r.lineheight)));
				mlx_put_pixel(game->w_id, (int) i, j, hex_color);
			}
			j++;
		}
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
		mlx_close_window(game->id);
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
