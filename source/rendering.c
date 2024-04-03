/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:40:25 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/03 18:41:18 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	render_floor_ceiling(t_map *game)
{
	int	x;
	int	y;

	y = 0;
	while (y <= WIN_HEIGHT)
	{
		x = 0;
		while (x <= WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				ft_put_pixel(game->w_id, x, y, game->graphics->ceiling);
			else
				ft_put_pixel(game->w_id, x, y, game->graphics->ground);
			x++;
		}
		y++;
	}
}

void	ft_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	bpp;

	bpp = sizeof(int32_t);
	img->pixels[(y * (WIN_WIDTH + 20) + x) * bpp + 0] = (uint8_t)(color >> 24);
	img->pixels[(y * (WIN_WIDTH + 20) + x) * bpp + 1] = (uint8_t)(color >> 16);
	img->pixels[(y * (WIN_WIDTH + 20) + x) * bpp + 2] = (uint8_t)(color >> 8);
	img->pixels[(y * (WIN_WIDTH + 20) + x) * bpp + 3] = (uint8_t)(150);
}

void	delete_textures(t_graphics *graphic)
{
	if (graphic->txtr_wall_n)
		mlx_delete_texture(graphic->txtr_wall_n);
	graphic->txtr_wall_n = NULL;
	if (graphic->txtr_wall_s)
		mlx_delete_texture(graphic->txtr_wall_s);
	graphic->txtr_wall_s = NULL;
	if (graphic->txtr_wall_e)
		mlx_delete_texture(graphic->txtr_wall_e);
	graphic->txtr_wall_e = NULL;
	if (graphic->txtr_wall_w)
		mlx_delete_texture(graphic->txtr_wall_w);
	graphic->txtr_wall_w = NULL;
}

int	texture_exists(t_graphics *graphic)
{
	int	fd;

	fd = open(graphic->path_wall_n, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(graphic->path_wall_s, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(graphic->path_wall_e, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(graphic->path_wall_w, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

int	create_images(t_map *game, t_graphics *graphic)
{
	graphic->txtr_wall_n = mlx_load_png(graphic->path_wall_n);
	graphic->txtr_wall_s = mlx_load_png(graphic->path_wall_s);
	graphic->txtr_wall_e = mlx_load_png(graphic->path_wall_e);
	graphic->txtr_wall_w = mlx_load_png(graphic->path_wall_w);
	if (!graphic->txtr_wall_n || !graphic->txtr_wall_s
		|| !graphic->txtr_wall_e || !graphic->txtr_wall_w)
		return (1);
	graphic->img_wall_n = mlx_texture_to_image(game->id, graphic->txtr_wall_n);
	graphic->img_wall_s = mlx_texture_to_image(game->id, graphic->txtr_wall_s);
	graphic->img_wall_e = mlx_texture_to_image(game->id, graphic->txtr_wall_e);
	graphic->img_wall_w = mlx_texture_to_image(game->id, graphic->txtr_wall_w);
	if (!graphic->img_wall_n || !graphic->img_wall_s || !graphic->img_wall_e
		|| !graphic->img_wall_w)
		return (1);
	return (0);
}
