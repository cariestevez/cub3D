/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:26:03 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/25 00:37:11 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include <math.h>

# define WIN_WIDTH 	960
# define WIN_HEIGHT 600
# define BPP sizeof(int32_t)// Bytes Per Pixel. Since each pixel is represented as an integer, it will be four bytes for four channels.
# define CEILING	'C'
# define FLOOR		'F'

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	camera;
}	t_player;

typedef struct s_graphics
{
	uint32_t		ceiling;
	uint32_t		ground;
	char			*path_wall_N;
	char			*path_wall_S;
	char			*path_wall_E;
	char			*path_wall_W;
	mlx_texture_t	*txtr_wall_N;
	mlx_texture_t	*txtr_wall_S;
	mlx_texture_t	*txtr_wall_E;
	mlx_texture_t	*txtr_wall_W;
	mlx_image_t		*img_wall_N;
	mlx_image_t		*img_wall_S;
	mlx_image_t		*img_wall_E;
	mlx_image_t		*img_wall_W;
}	t_graphics;

typedef struct s_map
{
	char			**matrix;
	t_graphics		*graphics;
	t_player		*player;
	mlx_image_t		 *w_id;
	mlx_t			*id;
}	t_map;

//main.c
int			args_check(int argc, char **argv);
int			ft_initgame(t_map *game);

//init.c
t_map		*init_struct(void);
t_graphics	*init_graphics(t_map *g);

//free.c
void		free_gnl_buff(int fd, char *line);
void		free_array(char **arr);
void		free_graphics(t_graphics *graphic);
void		free_struct(t_map *game);
void		ft_terminate(t_map *game);

//parsing.c
int			save_map_line(char *line, t_map *game);
int			parse_rgb(t_map *game, char **token);
int			parse_map(int fd, t_map *game, char **line);
int			parse_textures(int fd, t_map *game, char **line);
int 		parsing(char *map_file, t_map *game);

//validation_checks.c
int			is_closed(t_map *game);
int			save_rgb(char **rgb_char, char c, t_map *game);
int			validate_rgb(char c, char *raw_rgb, t_map *game);
int			save_textures(char **token, t_map *game);
int			validate_map(t_map *game);

//utils.c
int			is_empty_line(char *line);
void		ft_mlxerror(t_map *game);
void		ft_populate_player(t_map *game);
t_vector	ft_fill_vector(double x, double y);

//rendering.c
void		render_floor_ceiling(t_map *game);
int			create_images(t_map *game, t_graphics *graphics);
void		putpixel(int x, int y, int color);
void		ft_put_pixel(mlx_image_t *image, int x, int y, uint32_t color);

//game.c
void		ft_fake_game(t_map *game);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void		ft_randomize(void* param);
void		ft_raycast(void *param);

#endif
