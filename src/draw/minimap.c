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

void	draw_border(t_mlx *mlx_data, int start[2], int minimap_size[2])
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

void	draw_shadow(t_mlx *mlx_data, int start[2], int minimap_size[2])
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

void	draw_content(t_minimap *minimap_data, t_mlx *mlx_data, t_data *data)
{
	int		index[2];
	int		start[2];
	int		curr[2];

	index[X] = 0;
	start[X] = data->player->pos[X] - (minimap_data->tiles_horz / 2.0)
		* TILE_SIZE;
	start[Y] = data->player->pos[Y] - (TILES_VERTICAL / 2.0) * TILE_SIZE;
	while (index[X] < minimap_data->size[X] - 2)
	{
		index[Y] = 0;
		curr[X] = floor((start[X] + (index[X] * minimap_data->scale))
				/ TILE_SIZE);
		while (index[Y] < minimap_data->size[Y] - 2)
		{
			curr[Y] = floor((start[Y] + (index[Y] * minimap_data->scale))
					/ TILE_SIZE);
			if (curr[Y] < 0 || curr[X] < 0
				|| curr[X] >= data->map_data->max_width
				|| curr[Y] >= data->map_data->max_height)
				print_pixel_render(index[X] + minimap_data->start[X] + 1,
					index[Y] + minimap_data->start[Y] + 1,
					MINIMAP_BACK_COLOR, mlx_data);
			else
				print_tile_pixel(index[X] + minimap_data->start[X] + 1,
					index[Y] + minimap_data->start[Y] + 1,
					data->map_data->map[curr[Y]][curr[X]], mlx_data);
			index[Y]++;
		}
		index[X]++;
	}
}

void	draw_player(t_minimap *minimap_data, t_mlx *mlx_data)
{
	int	start_pos[2];
	int	index[2];
	int	square_size;

	square_size = minimap_data->tile_size / 3.0;
	if (square_size % 2 == 1)
		square_size++;
	start_pos[X] = minimap_data->start[X] + (minimap_data->size[X] / 2)
		- (square_size / 2);
	start_pos[Y] = minimap_data->start[Y] + (minimap_data->size[Y] / 2)
		- (square_size / 2);
	index[X] = 0;
	while (index[X] < square_size)
	{
		index[Y] = 0;
		while (index[Y] < square_size)
		{
			print_pixel_render(start_pos[X] + index[X], start_pos[Y] + index[Y],
				0xFF0000, mlx_data);
			index[Y]++;
		}
		index[X]++;
	}
}

void	create_minimap(t_minimap *minimap_data, t_mlx *mlx_data, t_data *data)
{
	draw_border(mlx_data, minimap_data->start, minimap_data->size);
	draw_shadow(mlx_data, minimap_data->start, minimap_data->size);
	draw_content(minimap_data, mlx_data, data);
	draw_player(minimap_data, mlx_data);
}
