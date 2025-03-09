/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:19:40 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/18 22:54:48 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//TODO Añadir pantalla final
void	finish_game(t_data *data)
{
	printf("Exit reached, no next level\n");
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	reset_map_data(t_data *data)
{
	free_map(data->map_data, data->mlx_data);
	if (data->cub_file)
		free_str_array(&data->cub_file);
	data->cub_file = NULL;
	data->map_data = malloc(sizeof(t_map));
	malloc_protection(data->map_data, data);
	init_map(data->map_data);
}

int	load_next_map(t_data *data)
{
	char	*next_map;

	if (data->map_data->next_map)
	{
		next_map = ft_strdup(data->map_data->next_map);
		reset_map_data(data);
		if (open_cub_file(next_map, data) == EXIT_FAILURE)
		{
			free(next_map);
			return (EXIT_FAILURE);
		}
		free(next_map);
		add_ui_textures(data);
		init_textures(data->map_data->txt_list, data->mlx_data, data);
		data->mlx_data->redraw = 1;
	}
	else
		finish_game(data);
	data->player->exit_reached = 0;
	return (0);
}
