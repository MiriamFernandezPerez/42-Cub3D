/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:32:12 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/03 00:26:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Receive a char** and free all of its contents
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

void	destroy_mlx(t_data *data)
{
	if (data->mlx_data)
	{
		if (data->mlx_data->img_ptr)
			mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->img_ptr);
		if (data->mlx_data->win_ptr)
			mlx_destroy_window(
				data->mlx_data->mlx_ptr, data->mlx_data->win_ptr);
		free(data->mlx_data->mlx_ptr);
		free(data->mlx_data);
		data->mlx_data = NULL;
	}
}

// Releases all map data
void	free_map(t_map *map_data)
{
	if (map_data->map)
		free_str_array(&(map_data->map));
	if (map_data->north_txt_path)
		free(map_data->north_txt_path);
	if (map_data->south_txt_path)
		free(map_data->south_txt_path);
	if (map_data->east_txt_path)
		free(map_data->east_txt_path);
	if (map_data->west_txt_path)
		free(map_data->west_txt_path);
	if (map_data->door_txt_path)
		free(map_data->door_txt_path);
	if (map_data->ceiling_txt_path)
		free(map_data->ceiling_txt_path);
	if (map_data->floor_txt_path)
		free(map_data->floor_txt_path);
	if (map_data->exit_sprite_path)
		free(map_data->exit_sprite_path);
	if (map_data->next_map)
		free(map_data->next_map);
	if (map_data->txt_list)
		clear_txt_list(&map_data->txt_list);
	free(map_data);
	map_data = NULL;
}

// Releases all the data necessary to finalize the program execution
void	free_data(t_data *data)
{
	if (data)
	{
		if (data->map_data)
			free_map(data->map_data);
		if (data->ray_data)
			free(data->ray_data);
		if (data->cub_file)
			free_str_array(&data->cub_file);
		if (data->player)
			free(data->player);
		if (data->mlx_data)
			destroy_mlx(data);
		if (data->minimap_data)
			free(data->minimap_data);
		free(data);
	}
}
