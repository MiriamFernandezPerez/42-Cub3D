/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:44:21 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/04 21:14:20 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//Creates t_map structure with hardcoded values
void	init_map_test(t_map	*map_data, t_data *data)
{
	map_data->map = malloc(sizeof(char *) * (5 + 1));
	map_data->map[5] = NULL;
	map_data->map[0] = ft_strdup("111111111111111");
	map_data->map[1] = ft_strdup("110000000011001");
	map_data->map[2] = ft_strdup("1001000N0000001");
	map_data->map[3] = ft_strdup("100000000000111");
	map_data->map[4] = ft_strdup("111111111111111");
	map_data->max_height = 5;
	map_data->max_width = 15;
	map_data->floor_color = 0xBBEFA8;
	map_data->ceiling_color = 0x8BDDE;
	data->player->angle = 180;
	data->player->pos[X] = 480;
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

//(TEST) Prints player debugger info
void	print_player_info(t_data *data)
{
	print_str(data->mlx_data, 10, 20, "Angle: ");
	print_nbr(data->mlx_data, 60, 20, data->player->angle);
	print_str(data->mlx_data, 10, 40, "Player[X]: ");
	print_nbr(data->mlx_data, 80, 40, data->player->pos[X]);
	print_str(data->mlx_data, 10, 60, "Player[Y]: ");
	print_nbr(data->mlx_data, 80, 60, data->player->pos[Y]);
}

//Function that prints number in the rendering window
void	print_nbr(t_mlx *mlx_data, int x, int y, int nbr)
{
	char	*str;

	str = ft_itoa(nbr);
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, x, y, 0xFFFFFF, str);
	free(str);
}

//Function that prints text in the rendering window
void	print_str(t_mlx *mlx_data, int x, int y, char *str)
{
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, x, y, 0xFFFFFF, str);
}

void	print_ray_data(t_raycast *ray_data)
{
	printf("----ALPHA %f -----\n", ray_data->alpha);
	printf("horz_hit [X]:%f [Y]:%f\n", ray_data->horz_hit[X],
		ray_data->horz_hit[Y]);
	printf("vert_hit [X]:%f [Y]:%f\n", ray_data->vert_hit[X],
		ray_data->vert_hit[Y]);
	printf("shortest_distance:%f ", ray_data->shortest_distance);
	if (ray_data->vtx_hit == X)
		printf("Vertex_hit: X\n");
	else
		printf("Vertex_hit: Y\n");
	printf("------------\n");

}
