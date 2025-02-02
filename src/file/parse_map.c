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

void	validate_map_border(t_data *data, char **map)
{
	int	i;
	int	j;
	int	row_len;

	i = -1;
	while (map[++i])
	{
		j = 0;
		row_len = ft_strlen(map[i]);
		while (j < row_len)
		{
			if (map[i][j] == '0' || ft_strchr("NSWE", map[i][j]))
			{
				if (i == 0 || j == 0 || !map[i + 1]
					|| j >= (int)ft_strlen(map[i + 1])
					|| (i > 0 && j < (int)ft_strlen(map[i - 1])
						&& map[i - 1][j] == ' ')
					|| (map[i + 1] && j < (int)ft_strlen(map[i + 1])
					&& map[i + 1][j] == ' ') || (j > 0 && map[i][j - 1] == ' ')
					|| (j < row_len - 1 && map[i][j + 1] == ' '))
					ft_error_exit(ERR_BORDER, data);
			}
			j++;
		}
	}
}

int	check_player(t_data *data, int i, int j)
{
	if (ft_strchr("NSWE", data->map_data->map[i][j]))
	{
		data->player->pos[Y] = (i * TILE_SIZE) + TILE_SIZE / 2;
		data->player->pos[X] = (j * TILE_SIZE) + TILE_SIZE / 2;
		data->player->coord[Y] = i;
		data->player->coord[X] = j;
		data->player->angle = calculate_angle(data->map_data->map, i, j);
		return (1);
	}
	return (0);
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

void	validate_map_tiles(t_data *data, char **map)
{
	int	i;
	int	j;
	int	player_qt;
	int	max_j;

	i = -1;
	player_qt = 0;
	max_j = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (check_player(data, i, j) == 1)
				player_qt++;
			else if (!ft_strchr("01DXC ", map[i][j]))
				ft_error_exit(ERR_INV_CHAR, data);
			if (max_j < j)
				max_j = j;
		}
	}
	if (player_qt != 1)
		ft_error_exit(ERR_PLAYER, data);
	data->map_data->max_width = max_j + 1;
	data->map_data->max_height = i;
}

void	parse_map(t_data *data, char **map_line)
{
	int		i;
	char	*line_trimmed;

	i = 0;
	while (map_line[i])
	{
		if (only_spaces(map_line[i]))
			ft_error_exit(ERR_MAP, data);
		line_trimmed = ft_strtrim(map_line[i], "\n");
		data->map_data->map = add_to_array(&data->map_data->map, line_trimmed);
		i++;
		free(line_trimmed);
	}
	if (!data->map_data->map)
		ft_error_exit(ERR_MAP, data);
	validate_map_tiles(data, data->map_data->map);
	normalize_map(data, data->map_data->map);
	validate_map_border(data, data->map_data->map);
	validate_map_route(data);
}
