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
	int		grid[2];
	double	hit[2];
	double	delta[2];

	if (data->player->angle > 270 && data->player->angle < 90)
		//Facing right
		//B.x = rounded_down(Px/64) * (64) + 64
		hit[X] = (floor(data->player->pos[X] / 64) * 64) + 64;
	else
		//Facing left
		//B.x = rounded_down(Px/64) * (64) - 1
		hit[X] = (floor(data->player->pos[X] / 64) * 64) - 1;

	//Grid B.X = rounded_down(B.x / 64);	
	grid[X] = (int)floor(hit[X] / 64);

	//B.y = Py + (Px-B.x)*tan(ALPHA); (ALPHA in radians);
	hit[Y] = data->player->pos[Y] + (data->player->pos[X] - hit[X])
	* tan(deg_to_rad(alpha));

	//Grid B.Y = rounded_down(B.y / 64);
	grid[Y] = (int)floor(hit[Y] / 64);
		
	//X increment	
	if (data->player->angle > 270 && data->player->angle < 90)
		//Facing right
		delta[X] = 64;
	else
		//Facing left
		delta[X] = -64;

	//delta[y] = 64 * tan(ALPHA);
	delta[Y] = 64 * tan(deg_to_rad(alpha));

	while (is_wall(grid, data->map_data) == 0)
	{
		hit[X] += delta[X];
		hit[Y] += delta[Y];
		grid[Y] = (int)floor(hit[Y] / 64);
		grid[X] = (int)floor(hit[X] / 64);
	}
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
	hit[X] = data->player->pos[X] + (data->player->pos[Y] - hit[Y])
		/ tan(deg_to_rad(alpha));

	//Grid A.X = rounded_down(A.x / 64);
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
	int		i;
	double alpha;

	i = 0;
	alpha = data->player->angle - 30;
	/*Raycasting*/

	//Primer angulo pixel 0 (pj angle + 30)
	//Bucle all pixels WIDTH
	while(i < WIDTH)
	{
		horz_wall_hit(alpha, ray_data, data);
		vert_wall_hit(alpha, ray_data, data);
		i++;
			//Calcular distancia
			//Calcular distancia real (sin distorsion)
			//Printar cielo
			//Printar muro
			//Printar suelo
		//Restar decremento angulo (izq a derecha resta)
	//fin bucle
	alpha -= ray_data->angle_increment;
	}	
}
