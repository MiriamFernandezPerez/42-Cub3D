/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:32:28 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/02 00:36:44 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_minimap_border(t_mlx *mlx_data, int start[2], int minimap_size[2])
{
	int	index[2];

	index[X] = start[X];
	while (index[X] < start[X] + minimap_size[X])
	{
		index[Y] = start[Y];
		while (index[Y] < start[Y] + minimap_size[Y])
		{
			if (index[X] == start[X]
				|| index[X] == start[X] + minimap_size[X] - 1
				|| index[Y] == start[Y]
				|| index[Y] == start[Y] + minimap_size[Y] - 1)
				print_pixel_render(
					index[X], index[Y], MINIMAP_BORDER_COLOR, mlx_data);
			index[Y]++;
		}
		index[X]++;
	}
}

void	draw_minimap_shadow(t_mlx *mlx_data, int start[2], int minimap_size[2])
{
	int	index[2];

	index[X] = start[X] - 1;
	while (index[X] < start[X] + minimap_size[X] + 1)
	{
		index[Y] = start[Y] - 1;
		while (index[Y] < start[Y] + minimap_size[Y] + 1)
		{
			if (index[X] == start[X] - 1
				|| index[X] == start[X] + minimap_size[X]
				|| index[Y] == start[Y] - 1
				|| index[Y] == start[Y] + minimap_size[Y])
				print_pixel_render(
					index[X], index[Y], MINIMAP_SHADOW_COLOR, mlx_data);
			index[Y]++;
		}
		index[X]++;
	}
}

void	draw_filled_rect(int pos[2], int size[2], int color, t_mlx *mlx_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < size[X])
	{
		j = 0;
		while (j < size[Y])
		{
			print_pixel_render(pos[X] + i, pos[Y] + j, color, mlx_data);
			j++;
		}
		i++;
	}
}

void	draw_minimap_content(t_minimap *minimap_data, t_mlx *mlx_data, t_data *data)
{
	int		index[2];
	int		map[2];
	float	offset[2];

	(void)mlx_data;

	// Calcular el offset del jugador dentro del tile
	offset[X] = fmod(data->player->pos[X], TILE_SIZE) / TILE_SIZE;
	offset[Y] = fmod(data->player->pos[Y], TILE_SIZE) / TILE_SIZE;
	printf("offset x:%f y:%f\n", offset[X], offset[Y]);

	// Determinar el primer tile visible en el minimapa
	map[X] = data->player->pos[X] / TILE_SIZE - minimap_data->tiles_horz / 2;
	map[Y] = data->player->pos[Y] / TILE_SIZE - TILES_VERTICAL / 2;
	printf("primer tile visible x:%d y:%d\n", map[X], map[Y]);

	// Posición inicial del minimapa en pantalla
	index[X] = 0;
	
	while (index[X] <  minimap_data->size[X] - 2)
	{
		index[Y] = 0;
		while (index[Y] < minimap_data->size[Y] - 2)
		{
			index[Y]++;
		}
		index[X]++;
	}

}

void	create_minimap(t_minimap *minimap_data, t_mlx *mlx_data, t_data *data)
{
	int	index[2];
	draw_minimap_border(mlx_data, minimap_data->start, minimap_data->size);
	draw_minimap_shadow(mlx_data, minimap_data->start, minimap_data->size);
	index[X] = minimap_data->start[X] + 1;
	printf("minimap->size: W:%d H:%d\n", minimap_data->size[X], minimap_data->size[Y]);
	printf("minimap->tile_size: %d\n", minimap_data->tile_size);
	
	
	while (index[X] < minimap_data->start[X] + minimap_data->size[X] - 1)
	{
		index[Y] = minimap_data->start[Y] + 1;
		while (index[Y] < minimap_data->start[Y] + minimap_data->size[Y] - 1)
		{
			print_pixel_render(index[X], index[Y], MINIMAP_BACK_COLOR, mlx_data);
			index[Y]++;
		}
		index[X]++;
	}
	draw_minimap_content(minimap_data, mlx_data, data);
}
