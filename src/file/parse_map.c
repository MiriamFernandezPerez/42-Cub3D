/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 01:35:11 by mirifern          #+#    #+#             */
/*   Updated: 2025/02/02 01:35:14 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_tiles_between_door(char **map, int y, int x, t_data *data)
{
	int grid[2];

	grid[0] = x;
	grid[1] = y;
	if ((map[y - 1]
			&& (map[y - 1][x] == TILE_FLOOR && map[y + 1][x] != TILE_FLOOR))
		|| (map[y - 1]
			&& (map[y - 1][x] == TILE_WALL && map[y + 1][x] != TILE_WALL))
		|| (map[x - 1]
			&& (map[y][x - 1] == TILE_FLOOR && map[y][x + 1] != TILE_FLOOR))
		|| (map[x - 1]
			&& (map[y][x - 1] == TILE_WALL && map[y][x + 1] != TILE_WALL)))
		return (1);
	else
	{
		if (map[y][x - 1] == TILE_WALL && map[y][x + 1] == TILE_WALL)
			add_door_node(grid, HORZ, data);
		else if (map[y - 1][x] == TILE_WALL && map[y + 1][x] == TILE_WALL)
			add_door_node(grid, VERT, data);
	}
	return (0);
}

void	validate_doors(t_data *data, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == TILE_DOOR)
			{
				if (check_tiles_between_door(map, y, x, data))
					ft_error_exit(ERR_DOOR, data);
			}
			x++;
		}
		y++;
	}
}

void	validate_map_border(t_data *data, t_map *map_data, char **map)
{
	int	i[2];

	i[Y] = -1;
	while (map[++i[Y]])
	{
		i[X] = -1;
		while (++i[X] < map_data->max_width)
		{
			if (map[i[Y]][i[X]] == TILE_FLOOR || map[i[Y]][i[X]] == TILE_N
				|| map[i[Y]][i[X]] == TILE_S || map[i[Y]][i[X]] == TILE_W
				|| map[i[Y]][i[X]] == TILE_EXIT)
			{
				if (i[Y] == 0 || i[X] == 0 || !map[i[Y] + 1]
					|| i[X] >= (int)ft_strlen(map[i[Y] + 1])
					|| (i[Y] > 0 && i[X] < (int)ft_strlen(map[i[Y] - 1])
						&& map[i[Y] - 1][i[X]] == ' ')
					|| (map[i[Y] + 1] && i[X] < (int)ft_strlen(map[i[Y] + 1])
					&& map[i[Y] + 1][i[X]] == ' ')
					|| (i[X] > 0 && map[i[Y]][i[X] - 1] == ' ')
					|| (i[X] < map_data->max_width - 1
						&& map[i[Y]][i[X] + 1] == ' '))
					ft_error_exit(ERR_BORDER, data);
			}
		}
	}
}

void	normalize_map(t_data *data, char **map)
{
	int		i;
	char	*new_row;
	int		len;

	i = 0;
	while (map[i])
	{
		len = (int)ft_strlen(map[i]);
		if (len == data->map_data->max_width)
			i++;
		else
		{
			new_row = malloc(data->map_data->max_width + 1);
			malloc_protection(new_row, data);
			ft_memcpy(new_row, map[i], len);
			ft_memset(new_row + len, ' ', data->map_data->max_width - len);
			new_row[data->map_data->max_width] = '\0';
			free(map[i]);
			map[i] = new_row;
		}
		i++;
	}
}

void	parse_map(t_data *data, char **map)
{
	int		i;
	int		j;
	int		k;
	char	*line_trimmed;

	i = -1;
	while (map[++i])
	{
		if (only_spaces(map[i]) || map[i][0] == '\n')
		{
			j = i - 1;
			while (map[++j])
			{
				k = -1;
				if (map[j][++k] != '\n')
					ft_error_exit(ERR_MAP, data);
			}
		}
		line_trimmed = ft_strtrim(map[i], "\n");
		data->map_data->map = add_to_array(&data->map_data->map, line_trimmed);
		free(line_trimmed);
	}
	if (!data->map_data->map)
		ft_error_exit(ERR_MAP, data);
}
