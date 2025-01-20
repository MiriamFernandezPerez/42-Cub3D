/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:05:41 by mirifern          #+#    #+#             */
/*   Updated: 2025/01/20 17:12:44 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/cub3d.h"

//Initializes data struct
void	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	malloc_protection(*data, NULL);
	(*data)->map_data = NULL;
	(*data)->cub_file = NULL;
}

//Main function
int	main(int ac, char **av)
{
	t_data *data;

	data = NULL;
	init_data(&data);
	if (check_args(ac, av) == EXIT_FAILURE)
		return (free_data(data), EXIT_FAILURE);
	if (open_file(av[1], data) == EXIT_FAILURE)
		return (free_data(data), EXIT_FAILURE);

	//TEST
	print_str_array(data->cub_file);

	return (free_data(data), EXIT_SUCCESS);
}
