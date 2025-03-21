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
#include "../../inc/audio.h"

//TODO Añadir pantalla final
void	finish_game(t_data *data)
{
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

void	select_song(t_data *data)
{
	if (data->player->level % 4 == 0)
	{
		stop_audio(WINTER_AUDIO, data);
		play_sound(SPRING_AUDIO, true, true, data);
	}
	else if (data->player->level % 4 == 1)
	{
		stop_audio(SPRING_AUDIO, data);
		play_sound(SUMMER_AUDIO, true, true, data);
	}
	else if (data->player->level % 4 == 2)
	{
		stop_audio(SUMMER_AUDIO, data);
		play_sound(AUTUMN_AUDIO, true, true, data);
	}
	else if (data->player->level % 4 == 3)
	{
		stop_audio(AUTUMN_AUDIO, data);
		play_sound(WINTER_AUDIO, true, true, data);
	}
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
		add_common_textures(data);
		init_textures(data->map_data->txt_list, data->mlx_data, data);
		data->player->level++;
		select_song(data);
	}
	else
		finish_game(data);
	data->player->exit_reached = 0;
	return (0);
}
