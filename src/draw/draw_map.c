/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/20 17:13:44 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_wall(int grid[2], t_map *map_data)
{
	if (map_data->map[grid[Y]][grid[X]] == TILE_WALL)
		return (1);
	return (0);
}

void	vert_wall_hit(double alpha, t_raycast *ray_data, t_data *data)
{
}

void	horz_wall_hit(double alpha, t_raycast *ray_data, t_data *data)
{
	int		grid[2];
	double	hit[2];
	double	delta[2];

	if (data->player->angle > 0 && data->player->angle < 180)
		//Facing up
		//A.y = rounded_down(Py/64) * (64) - 1;
		hit[Y] = (floor(data->player->pos[Y] / 64) * 64) - 1;
	else
		//Facing down
		//A.y = rounded_down(Py/64) * (64) + 64;
		hit[Y] = (floor(data->player->pos[Y] / 64) * 64) + 64;

	//Grid A.Y = rounded_down(A.y / 64);	
	grid[Y] = (int)floor(hit[Y] / 64);

	//A.x = Px + (Py-A.y)/tan(ALPHA); (ALPHA in radians);
	hit[X] = data->player->pos[X] + (data->player->pos[Y])
		/ tan(deg_to_rad(alpha));

	//Grid A.Y = rounded_down(A.y / 64);
	grid[X] = (int)floor(hit[X] / 64);

	//Y increment	
	if (data->player->angle > 0 && data->player->angle < 180)
		//Facing up
		delta[Y] = -64;
	else
		//Facing down
		delta[Y] = 64;
	
	//delta[X] = 64/tan(ALPHA);
	delta[X] = 64 / tan(deg_to_rad(alpha));

	while (is_wall(grid, data->map_data) == 0)
	{
		hit[X] += delta[X];
		hit[Y] += delta[Y];
		grid[Y] = (int)floor(hit[Y] / 64);
		grid[X] = (int)floor(hit[X] / 64);
	}
}

void	draw_map(t_raycast *ray_data, t_data *data)
{
	int	i;
	
	i = 0;
	/*Raycasting*/

	//Primer angulo pixel 0 (pj angle + 30)
	//Bucle all pixels WIDTH
	while(i < WIDTH)
	{
		find_intersect(X, ray_data, data);
		find_intersect(Y, ray_data, data);
		i++;
		//Buscar pixel (y) donde dibujar muro
			//Buscar intersecciones
				//Interseccion V
			//Calcular distancia
			//Calcular distancia real (sin distorsion)
			//Printar cielo
			//Printar muro
			//Printar suelo
		//Restar decremento angulo (izq a derecha resta)
	//fin bucle
	}	
}
