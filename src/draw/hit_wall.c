/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:19:40 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/25 21:59:10 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	reset_hit_data(t_raycast *ray_data)
{
	ray_data->horz_hit[X] = -1;
	ray_data->horz_hit[Y] = -1;
	ray_data->vert_hit[X] = -1;
	ray_data->vert_hit[Y] = -1;
}

int is_wall(int grid[2], t_map *map_data)
{
	if (map_data->map[grid[Y]][grid[X]] == TILE_WALL)
		return (1);
	return (0);
}


int	search_for_wall(int	grid[2], int hit[2], int delta[2], t_data *data)
{
	while (42)
	{
		// Grid B.X = rounded_down(B.x / TILE_SIZE);
		grid[X] = floor((double)hit[X] / TILE_SIZE);
		// Grid B.Y = rounded_down(B.y / TILE_SIZE);
		grid[Y] = floor((double)hit[Y] / TILE_SIZE);
		if (grid[X] < 0 || grid[X] >= data->map_data->max_width
			|| grid[Y] < 0 || grid[Y] >= data->map_data->max_height)
			return (0);
		if (is_wall(grid, data->map_data) == 1)
			break;
		hit[X] += delta[X];
		hit[Y] += delta[Y];
	}
	return (1);
}

void vert_wall_hit(double alpha, t_player *player, t_data *data)
{
	int grid[2];
	int hit[2];
	int delta[2];

	if (alpha >= 90 && alpha <= 270)
		// Facing left
		// B.x = rounded_down(Px/TILE_SIZE) * TILE_SIZE - 1
		hit[X] = floor(player->pos[X] / TILE_SIZE) * TILE_SIZE - 1;
	else if (alpha == 90 || alpha == 270)
		return ;
	else
		// Facing right
		// B.x = rounded_down(Px/TILE_SIZE) * TILE_SIZE + TILE_SIZE
		hit[X] = floor(player->pos[X] / TILE_SIZE) * TILE_SIZE + TILE_SIZE;

	// A.y = Py + (Px-A.x)*tan(ALPHA);
	// B.y = Py + (Px-B.x)*tan(ALPHA); (ALPHA in radians);
	hit[Y] = floor(player->pos[Y] + (player->pos[X] - hit[X])
		* tan(deg_to_rad(alpha)));

	// X increment
	if (alpha > 90 && alpha < 270)
		// Facing left
		delta[X] = -TILE_SIZE;
	else
		// Facing right
		delta[X] = TILE_SIZE;

	// delta[y] = TILE_SIZE * tan(ALPHA);
	delta[Y] = (int)floor(TILE_SIZE * tan(deg_to_rad(alpha)));
	if (alpha > 0 && alpha < 180)
		delta[Y] = -fabs((double)delta[Y]);
	else
		delta[Y] = fabs((double)(delta[Y]));

	if (search_for_wall(grid, hit, delta, data) == 0)
		return ;
	//Guardarme hit point X e Y
	printf("Vertical grid [%d][%d]\n", grid[X], grid[Y]);
	data->ray_data->vert_hit[X] = hit[X];
	data->ray_data->vert_hit[Y] = hit[Y];
}

void horz_wall_hit(double alpha, t_player *player, t_data *data)
{
	int grid[2];
	int hit[2];
	int	delta[2];

	if (alpha > 0 && alpha < 180)
		// Facing up
		// A.y = rounded_down(Py/TILE_SIZE) * TILE_SIZE - 1;
		hit[Y] = (int)(floor(player->pos[Y] / TILE_SIZE) * TILE_SIZE) - 1;
	else if (alpha == 0 || alpha == 180)
		return;
	else
		// Facing down
		// A.y = rounded_down(Py/TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		hit[Y] = (int)(floor(player->pos[Y] / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;


	// A.x = Px + (Py-A.y)/tan(ALPHA);
	hit[X] = (int)floor(player->pos[X] + (player->pos[Y] - hit[Y])
		/ tan(deg_to_rad(alpha)));

	// Y increment
	if (alpha > 0 && alpha < 180)
		// Facing up
		delta[Y] = -TILE_SIZE;
	else
		// Facing down
		delta[Y] = TILE_SIZE;

	// delta[X] = TILE_SIZE/tan(ALPHA);
	delta[X] = (int)floor(TILE_SIZE / tan(deg_to_rad(alpha)));
	if (alpha > 90 && alpha < 270)
		delta[X] = -fabs((double)delta[X]);
	else
		delta[X] = fabs((double)delta[X]);

	if (search_for_wall(grid, hit, delta, data) == 0)
		return (reset_hit_data(data->ray_data));

	//Guardarme el valor de hit X e Y
	data->ray_data->horz_hit[X] = hit[X];
	data->ray_data->horz_hit[Y] = hit[Y];
	printf("Horizontal grid [%d][%d]\n", grid[X], grid[Y]);
}
