/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdorado- <hdorado-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:49:09 by hdorado-          #+#    #+#             */
/*   Updated: 2024/04/01 16:40:22 by hdorado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// void	ft_fake_game(t_map *game)
// {
// 	char	**arr;

// 	arr = ft_calloc(12, sizeof(char *));
// 	int i = -1;
// 	while (++i < 11)
// 		arr[i] = ft_calloc(sizeof(char), 11);
// 	arr[0] = "1111111111";
// 	arr[1] = "1000000001";
// 	arr[2] = "1000000001";
// 	arr[3] = "1000000001";
// 	arr[4] = "1000000001";
// 	arr[5] = "1000000001";
// 	arr[6] = "1000000001";
// 	arr[7] = "1000000001";
// 	arr[8] = "1000000001";
// 	arr[9] = "1111111111";
// 	arr[10] = 0;
// 	game->matrix = arr;
// }

uint32_t	ft_get_pixel(mlx_image_t *image, double horizontal, double vertical)
{
	int			x;
	int			y;
	uint32_t	color;

	color = 0;
	if (horizontal >= 0)
		x = (int) (95 * horizontal); //95 is because the image is 96x96
	else
		x = (int) (95 * (1.0 + horizontal));
	y = (int) (95 * vertical);
	//printf("In the wall, print value (%d, %d) from (%f, %f)\n", x, y, horizontal, vertical);
	color += image->pixels[(y * 96 + x) * 4] << 24;
	color += image->pixels[(y * 96 + x) * 4 + 1] << 16;
	color += image->pixels[(y * 96 + x) * 4 + 2] << 8;
	color += image->pixels[(y * 96 + x) * 4 + 3];
	return (color);
}

void	ft_raycast(void *param)
{
	double	i;
	t_map	*game;
	t_vector	ray;
	double		section;
	uint32_t	hex_color;

	game = (t_map *) param;
	i = -1.0;
	int	k = -1;
	int	l;
	while (++k < 960)
	{
		l = -1;
		//while (++l < 600)
		//	mlx_put_pixel(game->w_id, k, l, ft_pixel(0x00, 0x00, 0x00, 0xFF));
	}
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
			deltaDistX = fabs(1/1e-30);
		else
			deltaDistX = fabs(1/ray.x);
		double deltaDistY;
		if (ray.y == 0)
			deltaDistY = fabs(1/1e-30);
		else
			deltaDistY = fabs(1/ray.y);
		int stepX; //Are we walking in the positive or negative direction?
		int	stepY;
		int	hit = 0; //was there a wall hit?
		int	side; //was a NS (0) or a EW (1) wall hit?
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
			if (game->matrix[mapY][mapX] == '1')
				hit = 1;
		}
		double WallDist; //How far is the wall based on the camera plane? No from player, as that would give us fisheye effect (round walls)
		if(side == 0)
			WallDist = (sideDistX - deltaDistX);
		else
			WallDist = (sideDistY - deltaDistY);
		//Now we calculate how big the wall should be, inversely proportional to WallDist, using the height of the screen so when we are in front of a wall, it takes up all the space
		int lineHeight;
		if (WallDist <= 0.001)
			lineHeight = (int) (600 / 0.001);
		else
			lineHeight = (int)(600/ WallDist);
		//calculate lowest and highest pixel to fill in current stripe: 0 is the center of the screen, so half the line should go negative and the other positive. If it's higher than the margins, stop at 0/highest margin
		int drawStart = -lineHeight / 2 + 600 / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + 600 / 2;
		if(drawEnd >= 600)
			drawEnd = 600 - 1;
		int	j = drawStart;
		//printf("For i=%d, x component is %f hits the wall at %f\n", (int) i, ray.x * WallDist, (ray.x * WallDist - ((int) (ray.x * WallDist)))*100);
		while (j <= drawEnd)
		{
			if (side && (int) mapY < (int) game->player->pos.y) //North
			{
				hex_color = ft_get_pixel(game->graphics->img_wall_N, (ray.x * WallDist + game->player->pos.x - ((int) (ray.x * WallDist + game->player->pos.x))), ((double)(((lineHeight - 600)/2) + j)) / ((double) (lineHeight)));
				mlx_put_pixel(game->w_id, (int) i, j, hex_color);
			}
			else if (side && (int) mapY > (int) game->player->pos.y) //South
			{
				hex_color = ft_get_pixel(game->graphics->img_wall_S, (ray.x * WallDist + game->player->pos.x - ((int) (ray.x * WallDist + game->player->pos.x))), ((double)(((lineHeight - 600)/2) + j)) / ((double) (lineHeight)));
				mlx_put_pixel(game->w_id, (int) i, j, hex_color);
			}
			else if (!side && (int) mapX > (int) game->player->pos.x) //East
			{
				hex_color = ft_get_pixel(game->graphics->img_wall_E, (ray.y * WallDist + game->player->pos.y - ((int) (ray.y * WallDist + game->player->pos.y))), ((double)(((lineHeight - 600)/2) + j)) / ((double) (lineHeight)));
				mlx_put_pixel(game->w_id, (int) i, j, hex_color);
			}
			else //West
			{
				hex_color = ft_get_pixel(game->graphics->img_wall_W, (ray.y * WallDist + game->player->pos.y - ((int) (ray.y * WallDist + game->player->pos.y))), ((double)(((lineHeight - 600)/2) + j)) / ((double) (lineHeight)));
				mlx_put_pixel(game->w_id, (int) i, j, hex_color);
			}
			j++;
		}
	}
}

void	move_camera(t_map *game, char dir)
{
	double	angle;
	//Angles are backward since "north" is negative. We want to calculate the angle between 0 and 2*PI radians
	//Reminder:
	//0 degrees = 360 degrees = 0 radians = 2*PI radians
	//90 degrees = PI/2
	//180 degrees = PI
	//270 degrees = 3*PI/2
	if (game->player->dir.y < 0 && game->player->dir.x >= 0)//If Y is positive but X negative, we are facing northwestish (0-90)
		angle = acos(game->player->dir.x); //Angle between 0-90 degrees, so this is good
	else if (game->player->dir.y >= 0 && game->player->dir.x >= 0)//We are facing southwestish (270-360)
		angle = 2*PI - acos(game->player->dir.x);//acos gives us only the 0-180 degrees, so we need to adjust the angle
	else if (game->player->dir.y >= 0 && game->player->dir.x < 0)//We are facing southeastish (180-270)
		angle = 2*PI - acos(game->player->dir.x);//Again, we need to adjust the angle
	else //We are facing norththeastish (90-180)
		angle = acos(game->player->dir.x); //acos works again
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
	{
		tmp.x = game->player->pos.x - 0.2 * game->player->dir.x;
		tmp.y = game->player->pos.y - 0.2 * game->player->dir.y;
	}
	else if (dir == 'E')
	{
		tmp.x = game->player->pos.x - 0.2 * game->player->dir.y;
		tmp.y = game->player->pos.y + 0.2 * game->player->dir.x;
	}
	else if (dir == 'W')
	{
		tmp.x = game->player->pos.x + 0.2 * game->player->dir.y;
		tmp.y = game->player->pos.y - 0.2 * game->player->dir.x;
	}
	if (t_wall_dist(game, tmp))
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
