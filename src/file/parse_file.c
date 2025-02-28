/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 01:30:57 by mirifern          #+#    #+#             */
/*   Updated: 2025/02/04 23:30:22 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*parse_path(char *line, t_data *data, char id)
{
	char	*path;

	path = ft_strtrim(line, " \t");
	if (!path || ft_strchr(path, ' '))
		ft_error_exit(ERR_TXT, data);
	if (id == ID_NORTH || id == ID_SOUTH || id == ID_WEST || id == ID_EAST
		|| id == ID_EXIT || id == ID_DOOR || id == ID_CHEST || id == ID_KEY
		|| id == ID_COIN)
		try_open_path(data, path);
	else if (id == ID_FLOOR || id == ID_CEIL)
		if (check_color_or_texture(data, path, id) == 1)
			return (free(path), NULL);
	if (id == ID_MAP)
	{
		if (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4))
			ft_error_exit(ERR_NEXT, data);
	}
	return (path);
}

int	parse_line(t_data *d, char *line)
{
	char	*trim_line;

	trim_line = ft_strtrim(line, "\t\n ");
	if (ft_strncmp(trim_line, NORTH_TXT, 3) == 0)
		add_texture_node(ID_NORTH, parse_path(trim_line + 3, d, ID_NORTH), d);
	else if (ft_strncmp(trim_line, SOUTH_TXT, 3) == 0)
		add_texture_node(ID_SOUTH, parse_path(trim_line + 3, d, ID_SOUTH), d);
	else if (ft_strncmp(trim_line, WEST_TXT, 3) == 0)
		add_texture_node(ID_WEST, parse_path(trim_line + 3, d, ID_WEST), d);
	else if (ft_strncmp(trim_line, EAST_TXT, 3) == 0)
		add_texture_node(ID_EAST, parse_path(trim_line + 3, d, ID_EAST), d);
	else if (ft_strncmp(trim_line, FLOOR, 2) == 0)
		add_texture_node(ID_FLOOR, parse_path(trim_line + 2, d, ID_FLOOR), d);
	else if (ft_strncmp(trim_line, CEIL, 2) == 0)
		add_texture_node(ID_CEIL, parse_path(trim_line + 2, d, ID_CEIL), d);
	else if (ft_strncmp(trim_line, DOOR, 2) == 0)
		add_texture_node(ID_DOOR, parse_path(trim_line + 2, d, ID_DOOR), d);
	else if (ft_strncmp(trim_line, EXIT, 5) == 0)
		add_texture_node(ID_EXIT, parse_path(trim_line + 5, d, ID_EXIT), d);
	else if (ft_strncmp(trim_line, CHEST, 6) == 0)
		add_texture_node(ID_CHEST, parse_path(trim_line + 6, d, ID_CHEST), d);
	else if (ft_strncmp(trim_line, KEY, 4) == 0)
		add_texture_node(ID_KEY, parse_path(trim_line + 4, d, ID_KEY), d);
	else if (ft_strncmp(trim_line, COIN, 5) == 0)
		add_texture_node(ID_COIN, parse_path(trim_line + 5, d, ID_COIN), d);
	else if (ft_strncmp(trim_line, NEXT_MAP, 5) == 0)
		d->map_data->next_map = parse_path(trim_line + 5, d, ID_MAP);
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
			if (parse_line(data, cub_file[i++]) == 1)
			{
				i--;
				break ;
			}
		}
	}
	parse_map(data, cub_file + i);
}
