/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/25 18:26:02 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"



void draw_map(t_raycast *ray_data, t_data *data)
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
		//
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
