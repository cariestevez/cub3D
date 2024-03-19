/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:26:03 by cestevez          #+#    #+#             */
/*   Updated: 2024/03/19 12:14:54 by cestevez         ###   ########.fr       */
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

# define WIN_WIDTH 	640
# define WIN_HEIGHT 640
# define WALL		'1'
# define GROUND		'0'
# define PL_NO      'N'
# define PL_SO		'S'
# define PL_EA      'E'
# define PL_WE		'W'

typedef struct s_map
{
	// size_t			height;
	// size_t			width;
	// size_t			item;
	// size_t			exit;
	size_t			start_y;
	size_t			start_x;
	//size_t			moves;
	char			**matrix;
	mlx_t			*mlx;
	char			*ceiling;
	char			*ground;
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
}	t_map;

//main.c
int	args_check(int argc, char **argv);
int	save_rgb(t_map *game, char **token);
int	save_textures(char **token, t_map *game);
int	parse_textures(int fd, t_map *game, char **line);
int	is_closed(t_map *game);
int	validate_map(t_map *game);
int	save_map_line(char *line, t_map *game);
int	is_empty_line(char *line);
int	parse_map(int fd, t_map *game, char **line);
int parsing(char *map_file, t_map *game);

//init.c
t_map	*init_game(void);
void	init_game_2(t_map *game);

//free.c
void	free_gnl_buff(int fd, char *line);
void	free_array(char **arr);
int		free_struct(t_map *game);


// int		parse_and_validate(t_map *game, char **argv);
// void	ft_mlxerror(t_map *game);
// int		ft_errors(int fd, t_map *game);

// //init_and_copy.c
// t_map	*init_game(t_map *game);
// t_map	*init_game_2(t_map *game);
// t_map	*init_map_copy(t_map *game, t_map *map_copy);
// t_map	*init_map_copy_2(t_map *game, t_map *map_copy);
// int		copy_map(t_map *game, t_map *map_copy);

// //pre_parsing.c
// int		free_gnl_buff(int fd, char *line);
// int		pre_parsing_check(t_map *game, int fd);
// int		invalid_char(char *line);
// int		check_shape(t_map *game, char *line);

// //parsing.c
// int		parse_map(int fd, t_map *game);
// void	save_line(t_map *game, size_t y, int fd);

// //validate_map.c
// int		validate_map(t_map *game);
// int		find_path(t_map *game);
// int		non_reachable(void);
// void	flood_fill(t_map *map_copy, size_t y, size_t x);

// //validation_checks.c
// int		check_walls(t_map *game);
// int		count_exit(t_map *game);
// int		count_plyr(t_map *game);
// int		count_item(t_map *game);

// //rendering.c
// void	create_images(t_map *game);
// void	display_images(t_map *game);
// void	layering(t_map *game);

// //key_handling.c
// void	my_keyhook(mlx_key_data_t keydata, void *param);
// void	check_surroundings(t_map *game, size_t y, size_t x, char c);
// void	move_player(t_map *game, char c);
// void	becauseofnormi(t_map *game);

// //free_exit.c
// int		free_inside_copy(t_map	*map_copy);
// int		free_matrix_exit(t_map	*game);
// int		free_and_exit(t_map	*game);

// //terminate_exit.c
// int		free_success_exit(t_map	*game);
// void	free_failure_exit(t_map	*game);
// void	free_textures(t_map	*game);
// void	free_and_terminate(t_map	*game);

#endif