/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 01:30:57 by mirifern          #+#    #+#             */
/*   Updated: 2025/02/02 01:30:58 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*parse_path(char *line, t_data *data, char id)
{
	char	*path;
	int		fd;

	path = ft_strtrim(line, " \t");
	if (!path || ft_strchr(path, ' '))
		ft_error_exit(ERR_TXT, data);
	if (id == ID_NORTH || id == ID_SOUTH || id == ID_WEST || id == ID_EAST
		|| id == ID_EXIT || id == ID_MAP)
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
			ft_error_exit(ERR_PATH, data);
		close(fd);
	}
	else if (id == ID_FLOOR || id == ID_CEIL || id == ID_DOOR)
		check_color_or_texture(data, path, id);
	if (id == ID_EXIT || id == ID_DOOR)
		check_exit_sprite(path, data, id);
	if (id == ID_MAP)
	{
		if (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4))
			ft_error_exit(ERR_NEXT, data);
	}
	return (path);
}

int	parse_line(t_data *data, t_map *map_data, char *line)
{
	char	*trim_line;

	trim_line = ft_strtrim(line, "\t\n ");
	if (ft_strncmp(trim_line, NORTH_TXT, 3) == 0)
		map_data->north_txt_path = parse_path(trim_line + 3, data, ID_NORTH);
	else if (ft_strncmp(trim_line, SOUTH_TXT, 3) == 0)
		map_data->south_txt_path = parse_path(trim_line + 3, data, ID_SOUTH);
	else if (ft_strncmp(trim_line, WEST_TXT, 3) == 0)
		map_data->west_txt_path = parse_path(trim_line + 3, data, ID_WEST);
	else if (ft_strncmp(trim_line, EAST_TXT, 3) == 0)
		map_data->east_txt_path = parse_path(trim_line + 3, data, ID_EAST);
	else if (ft_strncmp(trim_line, FLOOR, 2) == 0)
		map_data->floor_txt_path = parse_path(trim_line + 2, data, ID_FLOOR);
	else if (ft_strncmp(trim_line, CEIL, 2) == 0)
		map_data->ceiling_txt_path = parse_path(trim_line + 2, data, ID_CEIL);
	else if (ft_strncmp(trim_line, DOOR, 2) == 0)
		map_data->door_txt_path = parse_path(trim_line + 2, data, ID_DOOR);
	else if (ft_strncmp(trim_line, NEXT_MAP, 5) == 0)
		map_data->next_map = parse_path(trim_line + 5, data, ID_MAP);
	else if (ft_strncmp(trim_line, EXIT, 5) == 0)
		map_data->exit_sprite_path = parse_path(trim_line + 5, data, ID_EXIT);
	else
		return (free(trim_line), 1);
	return (free(trim_line), 0);
}

void	parse_cub_file(t_data *data, char **cub_file)
{
	int	i;

	i = 0;
	while (cub_file[i])
	{
		if (ft_strlen(cub_file[i]) == 0 || only_spaces(cub_file[i]))
			i++;
		else
		{
			if (parse_line(data, data->map_data, cub_file[i++]) == 1)
			{
				i--;
				break ;
			}
		}
	}
	validate_conf_textures(data);
	parse_map(data, cub_file + i);
}
