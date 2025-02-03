/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:54:14 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/03 01:57:01 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	try_open_path(t_data *data, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		ft_error_exit(ERR_PATH, data);
	}
	close(fd);
}

int	read_file(int fd, t_data *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		data->cub_file = add_to_array(&data->cub_file, line);
		malloc_protection(data->cub_file, data);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	if (!data->cub_file)
		return (ft_error(ERR_EMPTY), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	open_cub_file(char *path, t_data *data)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_perror(path), EXIT_FAILURE);
	if (read_file(fd, data) == EXIT_FAILURE)
	{
		close(fd);
		return (ft_perror(path), EXIT_FAILURE);
	}
	parse_cub_file(data, data->cub_file);
	validate_conf_textures(data);
	validate_doors(data, data->map_data->map);
	validate_map_tiles(data, data->map_data->map);
	normalize_map(data, data->map_data->map);
	validate_map_border(data, data->map_data, data->map_data->map);
	validate_map_route(data);
	//TODO Check only one exit (X)
	return (EXIT_SUCCESS);
}
