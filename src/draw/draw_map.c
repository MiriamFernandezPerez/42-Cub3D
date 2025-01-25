/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/25 21:59:32 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	find_hit_distance(t_player *player, t_raycast *ray_data)
{
	if (ray_data->horz_hit[X] > -1)
	{
		ray_data->h_distance = sqrt(pow(player->pos[X] - ray_data->horz_hit[X], 2)
			+ pow(player->pos[Y] - ray_data->horz_hit[Y], 2)); 
		printf("Px: %d Hx: %d Hy: %d\n", player->pos[X], ray_data->horz_hit[X], ray_data->horz_hit[Y]);
		printf("H distance: %f\n", ray_data->h_distance);
	}
	if (ray_data->vert_hit[X] > -1)
	{
		ray_data->v_distance = sqrt(pow(player->pos[X] - ray_data->vert_hit[X], 2)
			+ pow(player->pos[Y] - ray_data->vert_hit[Y], 2)); 
		printf("Px: %d Vx: %d Vy: %d\n", player->pos[X], ray_data->vert_hit[X], ray_data->vert_hit[Y]);
		printf("V distance: %f\n", ray_data->v_distance);
	}
}

void	draw_map(t_raycast *ray_data, t_data *data)
{
	int i;
	double alpha;

	i = 0;
	alpha = data->player->angle + FOV / 2;
	/*Raycasting*/

	// Primer angulo pixel 0 (pj angle + 30)
	// Bucle all pixels WIDTH
	while (i < WIDTH)
	{
		printf("---PRINTANDO ALPHA %f---\n", alpha);
		horz_wall_hit(alpha, data->player, data);
		vert_wall_hit(alpha, data->player, data);

		// Calcular distancia
	
		find_hit_distance(data->player, data->ray_data);

		// Calcular distancia real (sin distorsion)
		// Printar cielo
		// Printar muro
		// Printar suelo
		// Restar decremento angulo (izq a derecha resta)
		alpha -= ray_data->angle_increment;
		if (alpha < 0)
			alpha = 360 + alpha;
		i++;
		printf("--------------------\n");
	}
}
