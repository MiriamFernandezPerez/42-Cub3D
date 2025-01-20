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
	return (EXIT_SUCCESS);
}
