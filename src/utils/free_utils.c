/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:32:12 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/20 17:13:26 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//Receive a char** and free all of its contents
void	free_str_array(char ***str_array)
{
	int	i;

	i = 0;
	if (str_array && *str_array)
	{
		while ((*str_array)[i])
		{
			free((*str_array)[i]);
			(*str_array)[i] = NULL;
			i++;
		}
		free(*str_array);
		*str_array = NULL;
	}
}

//Releases all map data
void	free_map(t_map *map_data)
{
	if (map_data->map)
		free_str_array(&(map_data->map));
	if (map_data->north_texture_path)
		free(map_data->north_texture_path);
	if (map_data->south_texture_path)
		free(map_data->south_texture_path);
	if (map_data->east_texture_path)
		free(map_data->east_texture_path);
	if (map_data->west_texture_path)
		free(map_data->west_texture_path);
	if (map_data->floor)
		free(map_data->floor);
	if (map_data->ceiling)
		free(map_data->ceiling);
	if (map_data->player)
		free(map_data->player);
	free(map_data);
}

//Releases all the data necessary to finalize the program execution
void	free_data(t_data *data)
{
	if (data)
	{
		if (data->map_data)
			free_map(data->map_data);
		if (data->cub_file)
			free_str_array(&data->cub_file);
		free(data);
	}
}
