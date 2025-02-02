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
	if (id == 'N' || id == 'S' || id == 'W' || id == 'E'
		|| id == 'X' || id == 'M')
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
			ft_error_exit(ERR_PATH, data);
		close(fd);
	}
	else if (id == 'F' || id == 'C' || id == 'D')
		check_color_or_texture(data, path, id);
	if (id == 'X' || id == 'D')
		check_exit_sprite(path, data, id);
	if (id == 'M')
	{
		if (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4))
			ft_error_exit(ERR_NEXT, data);
	}
	return (path);
}

int	parse_line(t_data *data, char *line)
{
	char	*trim_line;

	trim_line = ft_strtrim(line, "\t\n ");
	if (ft_strncmp(trim_line, "NO ", 3) == 0)
		data->map_data->north_txt_path = parse_path(trim_line + 3, data, 'N');
	else if (ft_strncmp(trim_line, "SO ", 3) == 0)
		data->map_data->south_txt_path = parse_path(trim_line + 3, data, 'S');
	else if (ft_strncmp(trim_line, "WE ", 3) == 0)
		data->map_data->west_txt_path = parse_path(trim_line + 3, data, 'W');
	else if (ft_strncmp(trim_line, "EA ", 3) == 0)
		data->map_data->east_txt_path = parse_path(trim_line + 3, data, 'E');
	else if (ft_strncmp(trim_line, "F ", 2) == 0)
		data->map_data->floor_txt_path = parse_path(trim_line + 2, data, 'F');
	else if (ft_strncmp(trim_line, "C ", 2) == 0)
		data->map_data->ceiling_txt_path = parse_path(trim_line + 2, data, 'C');
	else if (ft_strncmp(trim_line, "D ", 2) == 0)
		data->map_data->door_txt_path = parse_path(trim_line + 2, data, 'D');
	else if (ft_strncmp(trim_line, "MAP ", 4) == 0)
		data->map_data->next_map = parse_path(trim_line + 4, data, 'M');
	else if (ft_strncmp(trim_line, "EXIT ", 5) == 0)
		data->map_data->exit_sprite_path = parse_path(trim_line + 5, data, 'X');
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
	validate_conf_textures(data);
	parse_map(data, cub_file + i);
}
