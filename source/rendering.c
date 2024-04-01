/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <hdorado-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:40:25 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/01 18:18:21 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	render_floor_ceiling(t_map *game)
{
	int	x;
	int y;

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

//This function will get the coordinates (x, y) in the image "image" that we want to paint with our color "color"
//Color is in the form of 0xRRGGBB
void		ft_put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	color = (uint32_t)color;

	//Check if x and y are within bounds (<WIDTH/HEIGHT)
	//We need to modify what's inside that address with the color that we want to use instead
	image->pixels[(y * WIN_WIDTH + x) * BPP + 0] = (uint8_t) (color >> 24);//red
	image->pixels[(y * WIN_WIDTH + x) * BPP + 1] = (uint8_t) (color >> 16);//green
	image->pixels[(y * WIN_WIDTH + x) * BPP + 2] = (uint8_t) (color >> 8); //blue
	image->pixels[(y * WIN_WIDTH + x) * BPP + 3] = (uint8_t) 0xFF; //alpha
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
	graphic->img_wall_N = mlx_texture_to_image(game->id, graphic->txtr_wall_N);
	graphic->img_wall_S = mlx_texture_to_image(game->id, graphic->txtr_wall_S);
	graphic->img_wall_E = mlx_texture_to_image(game->id, graphic->txtr_wall_E);
	graphic->img_wall_W = mlx_texture_to_image(game->id, graphic->txtr_wall_W);
	if (!graphic->img_wall_N || !graphic->img_wall_S || !graphic->img_wall_E
		|| !graphic->img_wall_W)
		return (1);
	return (0);
}
