/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:25:31 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/02 22:18:16 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	print_pixel_render(int x, int y, int color, t_mlx *mlx_data)
{
	int	pixel;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT || color == ALPHA_COLOR)
		return ;
	pixel = (y * mlx_data->line_len) + (x * (mlx_data->bpp / 8));
	mlx_data->new_img_addr[pixel] = color & 0xFF;
	mlx_data->new_img_addr[pixel + 1] = (color >> 8) & 0xFF;
	mlx_data->new_img_addr[pixel + 2] = (color >> 16) & 0xFF;
	if (mlx_data->bpp == 32)
		mlx_data->new_img_addr[pixel + 3] = (color >> 24);
}

void	print_tile_pixel(int x, int y, int map_idx[2], t_data *data)
{
	int	color;
	int	tile_type;

	if (map_idx[Y] < 0 || map_idx[X] < 0
		|| map_idx[X] >= data->map_data->max_width
		|| map_idx[Y] >= data->map_data->max_height)
		color = MINIMAP_BACK_COLOR;
	else
	{
		tile_type = data->map_data->map[map_idx[Y]][map_idx[X]];
		if (tile_type == TILE_WALL)
			color = MINIMAP_WALL_COLOR;
		else if (tile_type == TILE_FLOOR)
			color = MINIMAP_FLOOR_COLOR;
		else if (tile_type == TILE_SPACE)
			color = MINIMAP_BACK_COLOR;
		else if (tile_type == TILE_W || tile_type == TILE_N
			|| tile_type == TILE_S || tile_type == TILE_E)
			color = MINIMAP_FLOOR_COLOR;
		else if (tile_type == TILE_DOOR)
			color = MINIMAP_DOOR_COLOR;
	}
	print_pixel_render(x, y, color, data->mlx_data);
}

void	barycentric_weights(int vtx[3][2], int x, int y, float weights[3])
{
	weights[0] = ((vtx[1][Y] - vtx[2][Y]) * (x - vtx[2][X])
			+ (vtx[2][X] - vtx[1][X]) * (y - vtx[2][Y]))
		/ ((float)(vtx[1][Y] - vtx[2][Y]) *(vtx[0][X] - vtx[2][X])
			+ (vtx[2][X] - vtx[1][X]) * (vtx[0][Y] - vtx[2][Y]));
	weights[1] = ((vtx[2][Y] - vtx[0][Y]) * (x - vtx[2][X])
			+ (vtx[0][X] - vtx[2][X]) * (y - vtx[2][Y]))
		/ ((float)(vtx[1][Y] - vtx[2][Y]) *(vtx[0][X] - vtx[2][X])
			+ (vtx[2][X] - vtx[1][X]) * (vtx[0][Y] - vtx[2][Y]));
	weights[2] = 1 - weights[0] - weights[1];
}

void	print_triangle(int vtx[3][2], int color, t_mlx *mlx_data)
{
	int		min[2];
	int		max[2];
	int		index[2];
	float	weights[3];

	min[X] = fmin(vtx[0][X], fmin(vtx[1][X], vtx[2][X]));
	min[Y] = fmin(vtx[0][Y], fmin(vtx[1][Y], vtx[2][Y]));
	max[X] = fmax(vtx[0][X], fmax(vtx[1][X], vtx[2][X]));
	max[Y] = fmax(vtx[0][Y], fmax(vtx[1][Y], vtx[2][Y]));
	index[Y] = min[Y];
	while (index[Y] <= max[Y])
	{
		index[X] = min[X];
		while (index[X] <= max[X])
		{
			barycentric_weights(vtx, index[X], index[Y], weights);
			if (weights[0] >= 0 && weights[1] >= 0 && weights[2] >= 0)
				print_pixel_render(index[X], index[Y], color, mlx_data);
			index[X]++;
		}
		index[Y]++;
	}
}
