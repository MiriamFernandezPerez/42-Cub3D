/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:44:21 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/20 17:13:38 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//Creates t_map structure with hardcoded values
void	init_map_test(t_map	*map)
{
	map->map = malloc(sizeof(char *) * 5 + 1);
	map->map[0] = malloc(sizeof(char) * 5 + 1);	
	map->map[1] = malloc(sizeof(char) * 5 + 1);
	map->map[2] = malloc(sizeof(char) * 5 + 1);
	map->map[3] = malloc(sizeof(char) * 5 + 1);
	map->map[4] = malloc(sizeof(char) * 5 + 1);
	map->map[5] = NULL;
	map->map[0] = "11111";
	map->map[1] = "10001";
	map->map[2] = "10N01";
	map->map[3] = "10001";
	map->map[4] = "11111";
	map->max_height = 5;
	map->max_width = 5;
	map->north_texture_path = NULL;
	map->south_texture_path = NULL;
	map->west_texture_path = NULL;
	map->east_texture_path = NULL;
	map->floor = NULL;
	map->ceiling = NULL;
	map->player = malloc(sizeof(t_player));
	map->player->angle = 90;
	map->player->pos[0] = 160;	
	map->player->pos[1] = 160;
	map->next_map = NULL;
}

//(TEST) Receives a char** as a parameter and prints its content by console
void	print_str_array(char **str_array)
{
	int	i;

	i = 0;
	if (str_array)
	{
		while (str_array[i])
		{
			printf("[%d]: %s\n", i, str_array[i]);
			i++;
		}
	}
}
