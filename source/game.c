/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:49:09 by hdorado-          #+#    #+#             */
/*   Updated: 2024/03/26 00:02:44 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_fake_game(t_map *game)
{
	char	**arr;

	arr = ft_calloc(12, sizeof(char *));
	int i = -1;
	while (++i < 11)
		arr[i] = ft_calloc(sizeof(char), 11);
	arr[0] = "1111111111";
	arr[1] = "1000000001";
	arr[2] = "1000000001";
	arr[3] = "1000000001";
	arr[4] = "1000000001";
	arr[5] = "1000000001";
	arr[6] = "1000000001";
	arr[7] = "1000000001";
	arr[8] = "1000000001";
	arr[9] = "1111111111";
	arr[10] = 0;
	game->matrix = arr;
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_raycast(void *param)
{
	double	i;
	t_map	*game;
	t_vector	ray;
	double		section;

	game = (t_map *) param;
	i = -1.0;
	while (++i < 960) //For each (vertical column of) pixel in the screen
	{
		section = (2*i/959) - 1; //(959 because of 0), this will select each column
		ray.x = game->player->dir.x + game->player->camera.x*section; //Create the direction of the "ray of light", x coordinate
		ray.y = game->player->dir.y + game->player->camera.y*section; //Create the direction of the "ray of light", y coordinate
		int	mapX = (int)game->player->pos.x;
		int mapY = (int)game->player->pos.y;
		//Now we need to find how far away is the wall. This has two components, the sideDist (distance from current position until first border) and deltaDist (distance from first border to the next)
		double deltaDistX; //Find out the distance the ray needs to travel so it finds the next wall. If ray x or y is 0, divide by 1e30 to avoid division by 0
		if (ray.x == 0)
			deltaDistX = fabs(1/1e30);
		else
			deltaDistX = fabs(1/ray.x);
		double deltaDistY;
		if (ray.y == 0)
			deltaDistY = fabs(1/1e30);
		else
			deltaDistY = fabs(1/ray.y);
		int stepX; //Are we walking in the positive or negative direction?
		int	stepY;
		int	hit = 0; //was there a wall hit?
		int	side; //was a NS (1) or a EW (0) wall hit?
		double	sideDistX;
		double sideDistY;
		if (ray.x < 0)
		{
			stepX = -1;
			sideDistX = (game->player->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player->pos.x) * deltaDistX;
		}
		if (ray.y < 0)
		{
			stepY = -1;
			sideDistY = (game->player->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player->pos.y) * deltaDistY;
		}
		while (!hit)
		{
				//We will find the next step based on which side is shorter, so we will add deltaDist. The next sqaure in that direction will be sideDist+deltaDist away
				//After moving to the next border, we check if that border is a wall, to break the loop, or not. Since the room is surrounded by walls, we don't need to worry about going out of the map
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (game->matrix[mapX][mapY] == '1')
			{
				//printf("Position (%d, %d) is a wall! In the code is %d\n", mapX, mapY, game->matrix[mapX][mapY]);
				hit = 1;
			}
		}
		double WallDist; //How far is the wall based on the camera plane? No from player, as that would give us fisheye effect (round walls)
		if(side == 0)
			WallDist = (sideDistX - deltaDistX);
		else
			WallDist = (sideDistY - deltaDistY);
		//printf("WallDist is %f\n", WallDist);
		//Now we calculate how big the wall should be, inversely proportional to WallDist, using the height of the screen so when we are in front of a wall, it takes up all the space
		int lineHeight;
		if (WallDist == 0)
			lineHeight = 600;
		else
			lineHeight = (int)(600 / WallDist);
		//calculate lowest and highest pixel to fill in current stripe: 0 is the center of the screen, so half the line should go negative and the other positive. If it's higher than the margins, stop at 0/highest margin
		int drawStart = -lineHeight / 2 + 600 / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + 600 / 2;
		if(drawEnd >= 600)
			drawEnd = 600 - 1;
		int	j = drawStart;
		while (j <= drawEnd)
		{
			if (side)
				mlx_put_pixel(game->w_id, (int) i, j, ft_pixel(0xFF, 0x00, 0x00, 0x80));
			else
			{
				//printf("Side is good\n");
				mlx_put_pixel(game->w_id, (int) i, j, ft_pixel(0x00, 0xFF, 0x00, 0x80));
			}
			j++;
		}
	}
}

void ft_randomize(void* param)
{
	t_map *game;

	game = (t_map *)param;
	for (uint32_t i = 0; i < game->w_id->width; ++i)
	{
		for (uint32_t y = 0; y < game->w_id->height; ++y)
		{
			mlx_put_pixel(game->w_id, i, y, ft_pixel(0xFF, 0x00, 0x00, 0x80));
		}
	}
}
