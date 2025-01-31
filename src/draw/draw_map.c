/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/31 21:53:07 by igarcia2         ###   ########.fr       */
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
	//printf("beta: %f\n", beta);
	//printf("cos_beta: %f\n", cos(deg_to_rad(beta)));
    data->ray_data->corrected_distance =
		data->ray_data->shortest_distance * cos(deg_to_rad(beta));
	//printf("corrected_distance: %f\n", data->ray_data->corrected_distance);
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

	printf("horz_distance: %f\n", horz_distance);
	printf("vert_distance: %f\n", vert_distance);
	printf("shortest_distance: %f\n", ray_data->shortest_distance);
}

void	render_column(int x, char *img_addr, t_data *data)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (data->ray_data->wall_height >= HEIGHT)
			print_pixel(x, y, 0xA95C4C, data->mlx_data, img_addr);
		else
		{
			if (y < data->ray_data->wall_y)
				print_pixel(x, y, data->map_data->ceiling_color, data->mlx_data, img_addr);
			else if (y >= data->ray_data->wall_y
					&& y <= data->ray_data->wall_y + data->ray_data->wall_height)
				print_pixel(x, y, 0xA95C4C, data->mlx_data, img_addr);
			else
				print_pixel(x, y, data->map_data->floor_color, data->mlx_data, img_addr);
		}
		y++;
	}
	//eliminar?
	data->ray_data->wall_y = 0;
}

void	draw_map(t_raycast *ray_data, char *img_addr, t_data *data)
{
	int x;
	double alpha;

	x = 0;
	alpha = data->player->angle + FOV / 2;
	alpha = normalize_angle(alpha);
	/*Raycasting*/

	// Primer angulo pixel 0 (pj angle + 30)
	// Bucle all pixels WIDTH
	while (x < WIDTH)
	{
		printf("---PRINTANDO ALPHA %f---\n", alpha);
		horz_wall_hit(alpha, data->player, data);
		vert_wall_hit(alpha, data->player, data);
		// Calcular distancia
		find_shortest_hit_distance(data->player, data->ray_data);
		// Calcular distancia real (sin distorsion)
		calculate_corrected_distance(alpha, data);
		//Calculate projection_slice_height
		ray_data->wall_height = ceil((TILE_SIZE * (ray_data->distance_pp))
				/ ray_data->corrected_distance);

		if (ray_data->wall_height < HEIGHT)
			ray_data->wall_y = HEIGHT / 2 - ray_data->wall_height / 2;
		printf("wall_height: %d\n", ray_data->wall_height);

		// Printar column
		render_column(x, img_addr, data);	
		// Restar decremento angulo (izq a derecha resta)
		alpha -= ray_data->angle_increment;
		alpha = normalize_angle(alpha);
		x++;
		printf("--------------------\n");
	}
}
