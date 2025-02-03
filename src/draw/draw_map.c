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

	if (ray_data->horz_hit[X] > 0)
		horz_distance = sqrt(pow(player->pos[X] - ray_data->horz_hit[X], 2)
				+ pow(player->pos[Y] - ray_data->horz_hit[Y], 2));
	else
		horz_distance = -1;
	if (ray_data->vert_hit[X] > 0)
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
	if (ray_data->shortest_distance == horz_distance)
		ray_data->vector_hit = X;
	else
		ray_data->vector_hit = Y;
}

/*void	render_wall(int x, int y, t_raycast *ray_data, t_data *data)
{
	float	texture_x;
	double	alpha;

	alpha = ray_data->alpha;
	//calcular columna de la textura
	if (ray_data->vector_hit == X)
		texture_x = ray_data->horz_hit[X]
			- floor(ray_data->horz_hit[X] / TILE_SIZE) * TILE_SIZE;
	else
		texture_x = ray_data->vert_hit[Y]
			- floor(ray_data->vert_hit[Y] / TILE_SIZE) * TILE_SIZE;
	texture_x /= TILE_SIZE;

	//Encontrar textura orientacion
	if (ray_data->vector_hit == X && alpha > 0 && alpha < 180)
		texture_x *= (get_texture(ID_SOUTH, data)->width);
	else if (ray_data->vector_hit == X && alpha > 180 && alpha < 360)
		texture_x *= (get_texture(ID_NORTH, data)->width);
	else if (ray_data->vector_hit == Y && alpha > 90 && alpha < 270)
		texture_x *= (get_texture(ID_EAST, data)->width);
	else if (ray_data->vector_hit == Y)
		texture_x *= (get_texture(ID_WEST, data)->width);

}*/

void	render_column(int x, double alpha, t_data *data)
{
	int	y;
	alpha = alpha;

	y = 0;
	while (y < HEIGHT)
	{
		if (data->ray_data->wall_height >= HEIGHT)
			print_pixel_render(x, y, 0xA95C4C, data->mlx_data);
			//render_wall(x, y, data->ray_data, data);
		else
		{
			if (y < data->ray_data->wall_y)
				print_pixel_render(
					x, y, data->map_data->ceiling_color, data->mlx_data);
			else if (y >= data->ray_data->wall_y
				&& y <= data->ray_data->wall_y + data->ray_data->wall_height)
				print_pixel_render(x, y, 0xA95C4C, data->mlx_data);
				//render_wall(x, y, data->ray_data, data);
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

	x = 0;
	ray_data->alpha = data->player->angle + FOV / 2;
	ray_data->alpha = normalize_angle(ray_data->alpha);
	while (x < WIDTH)
	{
		horz_wall_hit(ray_data->alpha, data->player, data);
		vert_wall_hit(ray_data->alpha, data->player, data);
		find_shortest_hit_distance(data->player, data->ray_data);
		calculate_corrected_distance(ray_data->alpha, data);
		ray_data->wall_height = ceil((TILE_SIZE * (ray_data->distance_pp))
				/ ray_data->corrected_distance);
		if (ray_data->wall_height < HEIGHT)
			ray_data->wall_y = HEIGHT / 2 - ray_data->wall_height / 2;
		render_column(x, ray_data->alpha, data);
		ray_data->alpha -= ray_data->angle_increment;
		ray_data->alpha = normalize_angle(ray_data->alpha);
		/*printf("----ALPHA %f -----\n", ray_data->alpha);
		printf("horz_hit [X]:%f [Y]:%f\n", ray_data->horz_hit[X], ray_data->horz_hit[Y]);
		printf("vert_hit [X]:%f [Y]:%f\n", ray_data->vert_hit[X], ray_data->vert_hit[Y]);
		printf("------------\n");*/
		x++;
	}
}
