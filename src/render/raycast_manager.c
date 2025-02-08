/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/08 18:15:53 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	corrected_wall_distance(t_raycast *ray_data, t_data *data)
{
	double	beta;

	beta = ray_data->alpha - data->player->angle;
	beta = normalize_angle(beta);
	if (beta > 180)
		beta = (360 - beta);
	data->ray_data->corrected_distance
		= data->ray_data->shortest_distance * cos(deg_to_rad(beta));
	ray_data->wall_height = ceil((TILE_SIZE * (ray_data->distance_pp))
			/ ray_data->corrected_distance);
	if (ray_data->wall_height < HEIGHT)
		ray_data->wall_y = HEIGHT / 2 - ray_data->wall_height / 2;
	else
		ray_data->wall_y = 0;
}

void	fix_corner_case_intersection(double distance[2], t_raycast *ray_data,
		t_data *data)
{
	int	horz[2];
	int	vert[2];
	int	wall[2];

	horz[X] = (int)round((ray_data->horz_hit[X]) / TILE_SIZE);
	horz[Y] = (int)round((ray_data->horz_hit[Y]) / TILE_SIZE);
	vert[X] = (int)round((ray_data->vert_hit[X]) / TILE_SIZE);
	vert[Y] = (int)round((ray_data->vert_hit[Y]) / TILE_SIZE);
	if (ray_data->alpha > 90 && ray_data->alpha < 270)
		horz[X] -= 1;
	else
		vert[X] -= 1;
	if (ray_data->alpha > 0 && ray_data->alpha < 180)
		vert[Y] -= 1;
	else
		horz[Y] -= 1;
	wall[HORZ] = get_tile_type(horz, data->map_data);
	wall[VERT] = get_tile_type(vert, data->map_data);
	if (wall[VERT] == TILE_WALL || wall[VERT] == TILE_DOOR)
		distance[VERT] = 0;
	else
		distance[HORZ] = 0;
}

void	get_shortest_dist(t_player *player, t_raycast *ray_data, t_data *data)
{
	double	distance[2];

	if (ray_data->horz_hit[X] > 0)
		distance[HORZ] = sqrt(pow(player->pos[X] - ray_data->horz_hit[X], 2)
				+ pow(player->pos[Y] - ray_data->horz_hit[Y], 2));
	if (ray_data->vert_hit[X] > 0)
		distance[VERT] = sqrt(pow(player->pos[X] - ray_data->vert_hit[X], 2)
				+ pow(player->pos[Y] - ray_data->vert_hit[Y], 2));
	if (ray_data->vert_hit[X] <= 0)
		ray_data->shortest_distance = distance[HORZ];
	else if (ray_data->horz_hit[X] <= 0)
		ray_data->shortest_distance = distance[VERT];
	else if (distance[HORZ] < distance[VERT])
		ray_data->shortest_distance = distance[HORZ];
	else if (distance[VERT] < distance[HORZ])
		ray_data->shortest_distance = distance[VERT];
	if (fabs(distance[HORZ] - distance[VERT]) < EPSILON)
	{
		ray_data->shortest_distance = distance[HORZ];
		fix_corner_case_intersection(distance, ray_data, data);
	}
	if (ray_data->shortest_distance == distance[HORZ])
		ray_data->vtx_hit = X;
	else
		ray_data->vtx_hit = Y;
}

void	raycast_manager(t_raycast *ray_data, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	ray_data->alpha = data->player->angle + FOV / 2;
	while (x < WIDTH)
	{
		ray_data->alpha = normalize_angle(ray_data->alpha);
		y = 0;
		horz_wall_hit(ray_data->alpha, data->player, data);
		vert_wall_hit(ray_data->alpha, data->player, data);
		get_shortest_dist(data->player, data->ray_data, data);
		corrected_wall_distance(ray_data, data);
		while (y < HEIGHT)
		{
			if (y >= data->ray_data->wall_y
				&& y <= data->ray_data->wall_y + data->ray_data->wall_height)
				render_wall(x, &y, data->ray_data, data);
			else if (y > data->ray_data->wall_y + data->ray_data->wall_height)
				render_ceil_floor(x, &y, data);
			else
				y++;
		}
		//print_ray_data(ray_data); //TEST
		ray_data->alpha -= ray_data->angle_increment;
		x++;
	}
}
