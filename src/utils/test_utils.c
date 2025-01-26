/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:44:21 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/26 21:32:33 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//Creates t_map structure with hardcoded values
void	init_map_test(t_map	*map_data, t_data *data)
{
	map_data->map = malloc(sizeof(char *) * (5 + 1));
	map_data->map[5] = NULL;
	map_data->map[0] = ft_strdup("111111111111111");
	map_data->map[1] = ft_strdup("100000000000111");
	map_data->map[2] = ft_strdup("1000000000N0011");
	map_data->map[3] = ft_strdup("100100000000001");
	map_data->map[4] = ft_strdup("111111111111111");
	map_data->max_height = 5;
	map_data->max_width = 15;
	map_data->north_texture_path = NULL;
	map_data->south_texture_path = NULL;
	map_data->west_texture_path = NULL;
	map_data->east_texture_path = NULL;
	map_data->floor_color = 0xBBEFA8;
	map_data->ceiling_color = 0x8BDDE;
	data->player = malloc(sizeof(t_player));
	data->player->angle = 180;
	data->player->pos[X] = 544;	
	data->player->pos[Y] = 160;
	map_data->next_map = NULL;
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
