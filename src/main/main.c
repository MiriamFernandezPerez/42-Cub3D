/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:05:41 by mirifern          #+#    #+#             */
/*   Updated: 2025/01/22 18:48:40 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Initializes data struct
void init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	malloc_protection(*data, NULL);
	(*data)->cub_file = NULL;
	(*data)->map_data = NULL;
	(*data)->player = NULL;
	(*data)->ray_data = malloc(sizeof(t_raycast));
	malloc_protection((*data)->ray_data, *data);
	(*data)->ray_data->angle_increment = FOV / WIDTH;
	(*data)->ray_data->distance_pp = (WIDTH / 2) / (tan(FOV / 2));
	//(*data)->map_data = malloc(sizeof(t_map));
	// malloc_protection((*data)->map_data, *data);
	// Inicializar valores map_data
}

// Check if arg value is valid
int check_args(int ac, char **av)
{
	if (ac != 2)
		return (ft_error(ERR_ARGS), EXIT_FAILURE);
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
		return (ft_error(ERR_EXT), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// Main function
int main(int ac, char **av)
{
	t_data *data;

	data = NULL;
	if (check_args(ac, av) == EXIT_FAILURE)
		return (free_data(data), EXIT_FAILURE);
	// PARSE MAP
	init_data(&data);
	if (open_file(av[1], data) == EXIT_FAILURE)
		return (free_data(data), EXIT_FAILURE);
	print_str_array(data->cub_file);

	/*---------TEST---------
	init_map_test(data->map_data, data);
	------------------------*/
	// DRAW MAP
	draw_map(data->ray_data, data);
	return (free_data(data), EXIT_SUCCESS);
}
