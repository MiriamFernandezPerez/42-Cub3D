/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/01 18:52:40 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	calculate_corrected_distance(double alpha, t_data *data)
{
	double	beta;

	beta = alpha - data->player->angle;
	beta = normalize_angle(beta);
	if (beta > 180)
		beta = 360 - beta;
	data->ray_data->corrected_distance
		= data->ray_data->shortest_distance * cos(deg_to_rad(beta));
}

void	find_shortest_hit_distance(t_player *player, t_raycast *ray_data)
{
	double	horz_distance;
	double	vert_distance;

	if (ray_data->horz_hit[X] > -1)
		horz_distance = sqrt(pow(player->pos[X] - ray_data->horz_hit[X], 2)
				+ pow(player->pos[Y] - ray_data->horz_hit[Y], 2));
	else
		horz_distance = -1;
	if (ray_data->vert_hit[X] > -1)
		vert_distance = sqrt(pow(player->pos[X] - ray_data->vert_hit[X], 2)
				+ pow(player->pos[Y] - ray_data->vert_hit[Y], 2));
	else
		vert_distance = -1;
	if (vert_distance == -1)
		ray_data->shortest_distance = horz_distance;
	else if (horz_distance == -1)
		ray_data->shortest_distance = vert_distance;
	else if (horz_distance < vert_distance)
		ray_data->shortest_distance = horz_distance;
	else
		ray_data->shortest_distance = vert_distance;
}

void	render_column(int x, t_data *data)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (data->ray_data->wall_height >= HEIGHT)
			print_pixel_render(x, y, 0xA95C4C, data->mlx_data);
		else
		{
			if (y < data->ray_data->wall_y)
				print_pixel_render(
					x, y, data->map_data->ceiling_color, data->mlx_data);
			else if (y >= data->ray_data->wall_y
				&& y <= data->ray_data->wall_y + data->ray_data->wall_height)
				print_pixel_render(x, y, 0xA95C4C, data->mlx_data);
			else
				print_pixel_render(
					x, y, data->map_data->floor_color, data->mlx_data);
		}
		y++;
	}
}

void	draw_map(t_raycast *ray_data, t_data *data)
{
	int		x;
	double	alpha;

	x = 0;
	alpha = data->player->angle + FOV / 2;
	alpha = normalize_angle(alpha);
	while (x < WIDTH)
	{
		horz_wall_hit(alpha, data->player, data);
		vert_wall_hit(alpha, data->player, data);
		find_shortest_hit_distance(data->player, data->ray_data);
		calculate_corrected_distance(alpha, data);
		ray_data->wall_height = ceil((TILE_SIZE * (ray_data->distance_pp))
				/ ray_data->corrected_distance);
		if (ray_data->wall_height < HEIGHT)
			ray_data->wall_y = HEIGHT / 2 - ray_data->wall_height / 2;
		render_column(x, data);
		alpha -= ray_data->angle_increment;
		alpha = normalize_angle(alpha);
		x++;
	}
}
