/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/06 19:36:55 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	calculate_corrected_distance(double alpha, t_data *data)
{
	double	beta;

	beta = alpha - data->player->angle;
	beta = normalize_angle(beta);
	if (beta > 180)
		beta = (360 - beta);
	data->ray_data->corrected_distance
		= data->ray_data->shortest_distance * cos(deg_to_rad(beta));
}

void	fix_corner_case_intersection(double distance[2], t_raycast *ray_data,
		t_data *data)
{
	int	horz[2];
	int	vert[2];
	int	wall[2];

	horz[X] = (int)((ray_data->horz_hit[X] + EPSILON) / TILE_SIZE);
	horz[Y] = (int)((ray_data->horz_hit[Y] + EPSILON) / TILE_SIZE);
	vert[X] = (int)((ray_data->vert_hit[X] + EPSILON) / TILE_SIZE);
	vert[Y] = (int)((ray_data->vert_hit[Y] + EPSILON) / TILE_SIZE);
	printf("horz_hit[X]:%f horz_hit[Y]:%f\n", ray_data->horz_hit[X], ray_data->horz_hit[Y]);
	printf("vert_hit[X]:%f vert_hit[Y]:%f\n", ray_data->vert_hit[X], ray_data->vert_hit[Y]);

	if (ray_data->alpha > 90 && ray_data->alpha < 270)
		horz[X] -= 1;
	else
		vert[X] -= 1;
	if (ray_data->alpha > 0 && ray_data->alpha < 90)
		vert[Y] -= 1;
	else
		horz[Y] -= 1;
	wall[HORZ] = get_tile_type(horz, data->map_data);
	wall[VERT] = get_tile_type(vert, data->map_data);
	if (wall[VERT] == TILE_WALL)
		distance[VERT] = 0;
	else
		distance[HORZ] = 0;
	printf("horz[X]:%d horz[Y]%d\n", horz[X], horz[Y]);
	printf("vert[X]:%d vert[Y]%d\n", vert[X], vert[Y]);
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

void	render_column(int x, t_mlx *mlx_data, t_data *data)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < data->ray_data->wall_y)
			print_pixel_render(
				x, y, data->map_data->ceiling_color, mlx_data);
		else if (y >= data->ray_data->wall_y
			&& y <= data->ray_data->wall_y + data->ray_data->wall_height)
		{
			render_wall(x, &y, data->ray_data, data);
			y--;
		}
		else
			print_pixel_render(x, y, data->map_data->floor_color, mlx_data);
		y++;
	}
}

void	draw_map(t_raycast *ray_data, t_data *data)
{
	int		x;

	x = 0;
	ray_data->alpha = data->player->angle + FOV / 2;
	ray_data->alpha = normalize_angle(ray_data->alpha);
	while (x < WIDTH)
	{
		horz_wall_hit(ray_data->alpha, data->player, data);
		vert_wall_hit(ray_data->alpha, data->player, data);
		get_shortest_dist(data->player, data->ray_data, data);
		calculate_corrected_distance(ray_data->alpha, data);
		ray_data->wall_height = ceil((TILE_SIZE * (ray_data->distance_pp))
				/ ray_data->corrected_distance);
		if (ray_data->wall_height < HEIGHT)
			ray_data->wall_y = HEIGHT / 2 - ray_data->wall_height / 2;
		else
			ray_data->wall_y = 0;
		render_column(x, data->mlx_data, data);
		//print_ray_data(ray_data); //TEST
		ray_data->alpha -= ray_data->angle_increment;
		ray_data->alpha = normalize_angle(ray_data->alpha);
		x++;
	}
}
