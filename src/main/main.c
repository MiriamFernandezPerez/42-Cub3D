/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:05:41 by mirifern          #+#    #+#             */
/*   Updated: 2025/01/26 20:37:37 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_mlx(t_data *data)
{
	data->mlx_data = malloc(sizeof(t_mlx));
	malloc_protection(data->mlx_data, data);
	data->mlx_data->mlx_ptr = mlx_init();
	if (!data->mlx_data->mlx_ptr)
		ft_error_exit(ERR_MLX_INIT, data);
	data->mlx_data->win_ptr =
		mlx_new_window(data->mlx_data->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!data->mlx_data->win_ptr)
		ft_error_exit(ERR_MLX_WIN, data);
	data->mlx_data->img_ptr = NULL;
	data->mlx_data->img_addr = NULL;
	//COmprovar creacion img correcta
    data->mlx_data->redraw = 1;
	mlx_key_hook(data->mlx_data->win_ptr, key_hook, data); // Manejar eventos de teclado
	mlx_loop_hook(data->mlx_data->mlx_ptr, game_loop, data); // Vincular el bucle principal
}

void	init_map(t_map *map_data)
{
	map_data->map = NULL;
	map_data->max_height = 0;
	map_data->max_width = 0;
	map_data->north_texture_path = NULL;
	map_data->south_texture_path = NULL;
	map_data->east_texture_path = NULL;
	map_data->west_texture_path = NULL;
	map_data->floor = NULL;
	map_data->ceiling = NULL;
	map_data->ceiling_color = 0;
	map_data->floor_color = 0;
	map_data->next_map = NULL;
}

// Initializes data struct
void	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	malloc_protection(*data, NULL);
	(*data)->map_data = NULL;
	(*data)->ray_data = NULL;
	(*data)->mlx_data = NULL;
	(*data)->player = (t_player *)malloc(sizeof(t_player));
	malloc_protection((*data)->player, *data);
	(*data)->cub_file = NULL;
	(*data)->ray_data = malloc(sizeof(t_raycast));
	malloc_protection((*data)->ray_data, *data);
	(*data)->ray_data->angle_increment = (double)FOV / (double)WIDTH;
	(*data)->ray_data->distance_pp = (WIDTH / 2) / (tan(deg_to_rad(FOV / 2)));
	(*data)->map_data = malloc(sizeof(t_map));
	malloc_protection((*data)->map_data, *data);
	init_map((*data)->map_data);
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
	//init_map_test(data->map_data, data);

	// DRAW MAP
	init_mlx(data);
    mlx_loop(data->mlx_data->mlx_ptr);
	return (free_data(data), EXIT_SUCCESS);
}
