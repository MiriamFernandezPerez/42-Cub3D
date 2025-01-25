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

int is_wall(int grid[2], t_map *map_data)
{
	if (map_data->map[grid[Y]][grid[X]] == TILE_WALL)
		return (1);
	return (0);
}

void vert_wall_hit(double alpha, t_data *data)
{
	int grid[2];
	int hit[2];
	int delta[2];

	if (alpha >= 90 && alpha <= 270)
		// Facing left
		// B.x = rounded_down(Px/TILE_SIZE) * TILE_SIZE - 1
		hit[X] = (int)(floor(data->player->pos[X] / 64) * 64) - 1;
	else if (alpha == 90 || alpha == 270)
		return ;
	else
		// Facing right
		// B.x = rounded_down(Px/TILE_SIZE) * TILE_SIZE + TILE_SIZE
		hit[X] = (int)(floor(data->player->pos[X] / 64) * 64) + 64;



	// A.y = Py + (Px-A.x)*tan(ALPHA);
	// B.y = Py + (Px-B.x)*tan(ALPHA); (ALPHA in radians);
	hit[Y] = (int)floor(data->player->pos[Y] + (data->player->pos[X] - hit[X])
		* tan(deg_to_rad(alpha)));


	// X increment
	if (alpha > 90 && alpha < 270)
		// Facing left
		delta[X] = -64;
	else
		// Facing right
		delta[X] = 64;

	// delta[y] = TILE_SIZE * tan(ALPHA);
	delta[Y] = (int)floor(64 * tan(deg_to_rad(alpha)));
	if (alpha > 0 && alpha < 180)
		delta[Y] = -fabs(delta[Y]);
	else
		delta[Y] = fabs(delta[Y]);	
	printf("deltaY: %d\n", delta[Y]);

	while (42)
	{
		// Grid B.X = rounded_down(B.x / TILE_SIZE);
		grid[X] = (int)floor(hit[X] / 64);
		// Grid B.Y = rounded_down(B.y / TILE_SIZE);
		grid[Y] = (int)floor(hit[Y] / 64);
		if (grid[X] < 0 || grid[X] >= data->map_data->max_width
			|| grid[Y] < 0 || grid[Y] >= data->map_data->max_height)
			return;
		if (is_wall(grid, data->map_data) == 1)
			break;
		hit[X] += delta[X];
		hit[Y] += delta[Y];
	}
	printf("Vertical grid [%d][%d]\n", grid[X], grid[Y]);
}

void horz_wall_hit(double alpha, t_data *data)
{
	int grid[2];
	int hit[2];
	int	delta[2];

	if (alpha > 0 && alpha < 180)
		// Facing up
		// A.y = rounded_down(Py/TILE_SIZE) * TILE_SIZE - 1;
		hit[Y] = (int)(floor(data->player->pos[Y] / 64) * 64) - 1;
	else if (alpha == 0 || alpha == 180)
		return;
	else
		// Facing down
		// A.y = rounded_down(Py/TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		hit[Y] = (int)(floor(data->player->pos[Y] / 64) * 64) + 64;


	// A.x = Px + (Py-A.y)/tan(ALPHA);
	hit[X] = (int)floor(data->player->pos[X] + (data->player->pos[Y] - hit[Y])
		/ tan(deg_to_rad(alpha)));

	// Y increment
	if (alpha > 0 && alpha < 180)
		// Facing up
		delta[Y] = -64;
	else
		// Facing down
		delta[Y] = 64;

	// delta[X] = TILE_SIZE/tan(ALPHA);
	delta[X] = (int)floor(64 / tan(deg_to_rad(alpha)));
	if (alpha > 90 && alpha < 270)
		delta[X] = -fabs(delta[X]);
	else
		delta[X] = fabs(delta[X]);

	while (42)
	{
		// Grid A.Y = rounded_down(A.y / TILE_SIZE);
		grid[Y] = (int)floor(hit[Y] / 64);
		// Grid A.X = rounded_down(A.x / TILE_SIZE);
		grid[X] = (int)floor(hit[X] / 64);
		if (grid[X] < 0 || grid[X] >= data->map_data->max_width
			|| grid[Y] < 0 || grid[Y] >= data->map_data->max_height)
			return;
		if (is_wall(grid, data->map_data) == 1)
			break;
		hit[X] += delta[X];
		hit[Y] += delta[Y];
		}
	printf("HIT X: %d\n", hit[X]);
	printf("Horizontal grid [%d][%d]\n", grid[X], grid[Y]);
}

void draw_map(t_raycast *ray_data, t_data *data)
{
	int i;
	double alpha;

	i = 0;
	alpha = data->player->angle + 30;
	/*Raycasting*/

	// Primer angulo pixel 0 (pj angle + 30)
	// Bucle all pixels WIDTH
	while (i < WIDTH)
	{
		printf("---PRINTANDO ALPHA %f---\n", alpha);
		printf("%f\n", ray_data->angle_increment);
		horz_wall_hit(alpha, data);
		vert_wall_hit(alpha, data);
		// Calcular distancia
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
