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
	printf("PATH = %s", path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_perror(path), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*find_extension(char *line, int j)
{
	int		start;
	int 	len;
	char	*path;

	while (ft_isspace(line[j]))
		j++;
	start = j;
	while (!ft_isspace(line[j]) || line[j] != '\n')
		j++;
	len = ft_strlen(line) - start;
	path = ft_substr(line, start, len -1);
	if (check_texture_file(path) == 0)
		return (&line[j]);
	return (NULL);
}

void check_cube_file(t_data *data, char **cub_file)
{
	int i;
	int	j;

	i = 0;
	//Repetido??
	if (!cub_file)
		return(ft_error(ERR_EMPTY));
	while (cub_file[i])
	{
		j = 0;
		while (ft_isspace(cub_file[i][j]))
			j++;
		if (ft_strncmp(&cub_file[i][j], "NO", 2) == 0)
	       	data->map_data->north_texture_path = find_extension(cub_file[i], j + 2);
	    else if (ft_strncmp(&cub_file[i][j], "SO", 2) == 0)
            printf("SO\n");
        else if (ft_strncmp(&cub_file[i][j], "WE", 2) == 0)
            printf("WE\n");
        else if (ft_strncmp(&cub_file[i][j], "EA", 2) == 0)
            printf("EA\n");
        else if (ft_strncmp(&cub_file[i][j], "F", 1) == 0)
            printf("F\n");
        else if (ft_strncmp(&cub_file[i][j], "C", 1) == 0)
            printf("C\n");
        else
            printf("xx\n");
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
	check_cube_file(data, data->cub_file);
	return (EXIT_SUCCESS);
}
