/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:52:08 by hdorado-          #+#    #+#             */
/*   Updated: 2024/04/03 17:57:36 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

uint32_t	ft_get_pixel(mlx_image_t *image, double htal, double vcal)
{
	int			x;
	int			y;
	uint32_t	color;

	color = 0;
	if (htal >= 0)
		x = (int)(95 * htal);
	else
		x = (int)(95 * (1.0 + htal));
	y = (int)(95 * vcal);
	color += image->pixels[(y * 96 + x) * 4] << 24;
	color += image->pixels[(y * 96 + x) * 4 + 1] << 16;
	color += image->pixels[(y * 96 + x) * 4 + 2] << 8;
	color += image->pixels[(y * 96 + x) * 4 + 3];
	return (color);
}

void	ft_set_raycast(t_raycast *r, t_map *game)
{
	r->ray.x = game->player->dir.x + game->player->camera.x * r->section;
	r->ray.y = game->player->dir.y + game->player->camera.y * r->section;
	r->mapx = (int)game->player->pos.x;
	r->mapy = (int)game->player->pos.y;
	if (r->ray.x == 0)
		r->d_dist.x = fabs(1 / 1e-30);
	else
		r->d_dist.x = fabs(1 / r->ray.x);
	if (r->ray.y == 0)
		r->d_dist.y = fabs(1 / 1e-30);
	else
		r->d_dist.y = fabs(1 / r->ray.y);
}

void	ft_get_sidedist(t_raycast *r, t_map *game)
{
	if (r->ray.x < 0)
	{
		r->stepx = -1;
		r->s_dist.x = (game->player->pos.x - r->mapx) * r->d_dist.x;
	}
	else
	{
		r->stepx = 1;
		r->s_dist.x = (r->mapx + 1.0 - game->player->pos.x) * r->d_dist.x;
	}
	if (r->ray.y < 0)
	{
		r->stepy = -1;
		r->s_dist.y = (game->player->pos.y - r->mapy) * r->d_dist.y;
	}
	else
	{
		r->stepy = 1;
		r->s_dist.y = (r->mapy + 1.0 - game->player->pos.y) * r->d_dist.y;
	}
}

void	ft_find_wall(t_raycast *r, t_map *game)
{
	r->hit = 0;
	while (!r->hit)
	{
		if (r->s_dist.x < r->s_dist.y)
		{
			r->s_dist.x += r->d_dist.x;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->s_dist.y += r->d_dist.y;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (game->matrix[r->mapy][r->mapx] == '1')
			r->hit = 1;
	}
	if (r->side == 0)
		r->walldist = (r->s_dist.x - r->d_dist.x);
	else
		r->walldist = (r->s_dist.y - r->d_dist.y);
}

void	ft_draw(t_raycast *r, t_map *game, int i)
{
	int			j;
	double		p;
	uint32_t	hex;
	double		pv;
	double		ph;

	j = r->drawstart;
	pv = r->ray.x * r->walldist + game->player->pos.x;
	ph = r->ray.y * r->walldist + game->player->pos.y;
	while (j <= r->drawend)
	{
		p = ((double)(((r->lineheight - 600) / 2) + j)) / (r->lineheight);
		if (r->side && (int) r->mapy < (int) game->player->pos.y)
			hex = ft_get_pixel(game->graphics->img_wall_n, (pv - (int) pv), p);
		else if (r->side && (int) r->mapy > (int) game->player->pos.y)
			hex = ft_get_pixel(game->graphics->img_wall_s, (pv - (int) pv), p);
		else if (!r->side && (int) r->mapx > (int) game->player->pos.x)
			hex = ft_get_pixel(game->graphics->img_wall_e, (ph - (int) ph), p);
		else
			hex = ft_get_pixel(game->graphics->img_wall_w, (ph - (int) ph), p);
		ft_put_pixel(game->w_id, i, j, hex);
		j++;
	}
}
