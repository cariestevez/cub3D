/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:26:03 by cestevez          #+#    #+#             */
/*   Updated: 2024/04/03 15:27:11 by cestevez         ###   ########.fr       */
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
# define PI			3.14159265
# define CEILING	'C'
# define FLOOR		'F'
# define WALL		'1'
# define GROUND		'0'
# define PL_NO      'N'
# define PL_SO		'S'
# define PL_EA      'E'
# define PL_WE		'W'

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
	unsigned long	ceiling;
	unsigned long	ground;
	char			*path_wall_n;
	char			*path_wall_s;
	char			*path_wall_e;
	char			*path_wall_w;
	mlx_texture_t	*txtr_wall_n;
	mlx_texture_t	*txtr_wall_s;
	mlx_texture_t	*txtr_wall_e;
	mlx_texture_t	*txtr_wall_w;
	mlx_image_t		*img_wall_n;
	mlx_image_t		*img_wall_s;
	mlx_image_t		*img_wall_e;
	mlx_image_t		*img_wall_w;
}	t_graphics;

typedef struct s_map
{
	char			**matrix;
	t_graphics		*graphics;
	t_player		*player;
	mlx_image_t		*w_id;
	mlx_t			*id;
}	t_map;

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

//main.c
void		ft_terminate(t_map *game);
int			ft_initgame(t_map *game);
int			parsing(char *map_file, t_map *game);
int			args_check(int argc, char **argv);

//init.c
t_map		*init_struct(void);
t_graphics	*init_graphics(t_map *g);

//free.c
void		free_gnl_buff(int fd, char *line);
void		free_array(char **arr);
void		free_graphics(t_graphics *graphic);
void		free_struct(t_map *game);
void		ft_mlxerror(t_map *game);

//parsing.c
int			parse_rgb(t_map *game, char **token);
int			save_textures(char **token, t_map *game);
int			parse_textures(int fd, t_map *game, char **line);
int			inspect_map(t_map *game, int i, int j, int *n_player);
int			parse_map(int fd, t_map *game, char **line);

//validation_checks.c
int			is_closed(t_map *game);
void		ft_populate_player(t_map *game, int x, int y, char dir);
int			validate_map(t_map *game);
int			save_rgb(char **rgb_char, char c, t_map *game);
int			validate_rgb(char c, char *raw_rgb, t_map *game);

//utils.c
char		*trim_nl(char **line);
void		ft_read(char **line, int fd);
int			is_empty_line(char *line);
t_vector	ft_fill_vector(double x, double y);
int			save_map_line(char *line, t_map *game);

//rendering.c
void		render_floor_ceiling(t_map *game);
void		ft_put_pixel(mlx_image_t *image, int x, int y, uint32_t color);
int			create_images(t_map *game, t_graphics *graphics);

//game.c
void		ft_raycast(void *param);
void		move_camera(t_map *game, char dir);
int			ft_wall_dist(t_map *game, t_vector tmp_pos);
void		move_player(t_map *game, char dir);
void		ft_my_keys(mlx_key_data_t keydata, void *param);

//raycast_utils.c
uint32_t	ft_get_pixel(mlx_image_t *image, double htal, double vcal);
void		ft_set_raycast(t_raycast *r, t_map *game);
void		ft_get_sidedist(t_raycast *r, t_map *game);
void		ft_find_wall(t_raycast *r, t_map *game);
void		ft_draw(t_raycast *r, t_map *game, int i);

#endif
