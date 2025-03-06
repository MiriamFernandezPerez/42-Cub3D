/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:58:02 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/18 20:14:28 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_angle_in_fov(double angle, t_data *data)
{
	double	left_fov;
	double	right_fov;

	left_fov = normalize_angle(data->player->angle - (FOV / 2));
	right_fov = normalize_angle(data->player->angle + (FOV / 2));
	if (left_fov < right_fov)
	{
		if (angle < left_fov || angle > right_fov)
			return (0);
	}
	else
	{
		if (angle > right_fov && angle < left_fov)
			return (0);
	}
	return (1);
}

/*int	get_floor_color(int x, int y, t_minimap *minimap_data, t_data *data)
{
	double	world[2];
	double	distance;
	double	angle_to_point;
	int		pixel_index;

	world[X] = ((data->player->pos[X] - (minimap_data->tiles_horz / 2.0) * TILE_SIZE) + ((x - (minimap_data->start[X] + 1)) * minimap_data->scale));
	world[Y] = ((data->player->pos[Y] - (TILES_VERTICAL / 2.0) * TILE_SIZE) + ((y - (minimap_data->start[Y] + 1)) * minimap_data->scale));
	//printf("world x:%f y:%f\n", world[X], world[Y]);
	distance = calculate_distance(data->player->pos[X], data->player->pos[Y],
		world[X], world[Y]);
	angle_to_point = atan2(world[Y] - data->player->pos[Y], world[X] - data->player->pos[X]) * (180.0 / M_PI);
	if (angle_to_point < 0)
    angle_to_point += 360.0;  // Asegura que el ángulo esté en [0, 360]
	//Comprobar si el angulo está dentro del fov del player
	if (!is_angle_in_fov(angle_to_point, data))
		return (MINIMAP_FLOOR_COLOR);
	pixel_index = (int)((angle_to_point - (data->player->angle - (FOV / 2))) / FOV * WIDTH);
if (pixel_index < 0)
		pixel_index += WIDTH;
	else if (pixel_index >= WIDTH)
		pixel_index = WIDTH - 1;
	//printf("distance:%f\n", distance);i
	//printf("distance X=%d  :%f\n", pixel_index, minimap_data->shortest_distances[pixel_index]);
	//printf("pixel index: %d\n", pixel_index);
	if (distance <= minimap_data->shortest_distances[pixel_index])
		return (0xFFFFFF);
	return (MINIMAP_FLOOR_COLOR);
}*/

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
		else if (tile_type == TILE_SPACE)
			color = MINIMAP_BACK_COLOR;
		else if (tile_type == TILE_DOOR)
			color = MINIMAP_DOOR_COLOR;
		else
			color = MINIMAP_FLOOR_COLOR;
	}
	print_gui_pixel(x, y, color, data->mlx_data);
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
				print_gui_pixel(index[X], index[Y], color, mlx_data);
			index[X]++;
		}
		index[Y]++;
	}
}
