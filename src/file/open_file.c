/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:54:14 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/20 17:13:06 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int check_texture_file(char *path)
{
	int	fd;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_perror(path), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*find_path(t_data *data, char *line, int j)
{
	int		start;
	int 	len;
	char	*path;

	while (ft_isspace(line[j]))
		j++;
	start = j;
	while (!ft_isspace(line[j]) || line[j] != '\n')
		j++;
	len = ft_strlen(line) - start - 1;
	path = ft_substr(line, start, len);
	printf("%s\n", path);
	if (check_texture_file(path) == 0)
		return (path);
	else
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
}

void	check_cube_file(t_data *data, char **cub_file, int i, int j)
{
	while (cub_file[i])
	{
		j = 0;
		while (ft_isspace(cub_file[i][j]))
			j++;
		if (ft_strncmp(&cub_file[i][j], "NO", 2) == 0)
	       	data->map_data->north_texture_path = find_path(data, cub_file[i], j + 2);
	    else if (ft_strncmp(&cub_file[i][j], "SO", 2) == 0)
            data->map_data->south_texture_path = find_path(data, cub_file[i], j + 2);
        else if (ft_strncmp(&cub_file[i][j], "WE", 2) == 0)
            data->map_data->west_texture_path = find_path(data, cub_file[i], j + 2);
        else if (ft_strncmp(&cub_file[i][j], "EA", 2) == 0)
            data->map_data->east_texture_path = find_path(data, cub_file[i], j + 2);
        else if (ft_strncmp(&cub_file[i][j], "F", 1) == 0)
            data->map_data->floor = find_path(data, cub_file[i], j + 1);
        else if (ft_strncmp(&cub_file[i][j], "C", 1) == 0)
            data->map_data->floor = find_path(data, cub_file[i], j + 1);
        /*else if (ft_strncmp(&cub_file[i][j], "X", 1) == 0)
            data->map_data->next_map = find_path(data, cub_file[i], j + 1);*/
		i++;
	}
}

int	read_file(int fd, t_data *data)
{
	char *line;

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
		ft_error_exit(ERR_EMPTY, data);
	return (EXIT_SUCCESS);
}

//Opens file from path
int	open_file(char *path, t_data *data)
{
	int	fd;
	
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_perror(path), EXIT_FAILURE);
	if (read_file(fd, data) == EXIT_FAILURE)
		return (ft_perror(path), EXIT_FAILURE);
	check_cube_file(data, data->cub_file, 0, 0);
	return (EXIT_SUCCESS);
}
