/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:32:28 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/02 02:02:04 by igarcia2         ###   ########.fr       */
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

void	draw_minimap_content(t_minimap *minimap_data, t_mlx *mlx_data, t_data *data)
{
	int		index[2];
	int		start[2];
	int		current[2];

	index[X] = 0;
	start[X] = data->player->pos[X] - (minimap_data->tiles_horz / 2) * 64;
	start[Y] = data->player->pos[Y] - (TILES_VERTICAL / 2) * 64;
	while (index[X] <  minimap_data->size[X] - 2)
	{
		index[Y] = 0;
		current[X] = (start[X] + (index[X] * minimap_data->scale)) / TILE_SIZE;
		while (index[Y] < minimap_data->size[Y] - 2)
		{
			current[Y] = (start[Y] + (index[Y] * minimap_data->scale)) / TILE_SIZE;
			if (current[Y] < 0 || current[X] < 0 || current[X] > data->map_data->max_width
					|| current[Y] > data->map_data->max_height)
				print_pixel_render(index[X] + minimap_data->start[X] + 1,
					index[Y] + minimap_data->start[Y] + 1, 0x000000, mlx_data);
			else if (data->map_data->map[current[Y]][current[X]] == TILE_WALL)
				print_pixel_render(index[X] + minimap_data->start[X] + 1,
					index[Y] + minimap_data->start[Y] + 1, 0xFFFFFF, mlx_data);
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
