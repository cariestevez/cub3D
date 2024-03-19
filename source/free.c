#include "../include/cub3D.h"

void	free_gnl_buff(int fd, char *line)
{
	//line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

int	free_struct(t_map *game)
{
	free(game->ceiling);
	free(game->ground);
	free(game->path_wall_N);
	free(game->path_wall_S);
	free(game->path_wall_E);
	free(game->path_wall_W);
	free(game->txtr_wall_N);
	free(game->txtr_wall_S);
	free(game->txtr_wall_E);
	free(game->txtr_wall_W);
	free(game->img_wall_N);
	free(game->img_wall_S);
	free(game->img_wall_E);
	free(game->img_wall_W);
	free_array(game->matrix);
	free(game->mlx);
	return (0);
}