/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:19:40 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/18 22:54:48 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_door(int x, int *y, t_raycast *ray_data, t_data *data)
{
	float		texture_vtx[2];
	float		y_step;
	t_texture	*texture;

	if (ray_data->vtx_hit == HORZ)
		texture_vtx[X] = fmod(
				ray_data->horz_hit[X] - ray_data->door->offset, TILE_SIZE);
	else
		texture_vtx[X] = fmod(
				ray_data->vert_hit[Y] - ray_data->door->offset, TILE_SIZE);
	texture = get_texture(ID_DOOR, data);
	texture_vtx[X] = (texture_vtx[X] / TILE_SIZE) * texture->width;
	texture_vtx[Y] = 0.0f;
	y_step = (float)texture->height / ray_data->wall_height;
	if (ray_data->wall_height >= HEIGHT)
		texture_vtx[Y] = ((ray_data->wall_height - HEIGHT) / 2) * y_step;
	while (*y >= ray_data->wall_y
		&& *y <= ray_data->wall_y + ray_data->wall_height && *y < HEIGHT)
	{
		print_pixel_render(x, *y, get_texture_pixel(texture,
				fmod(texture_vtx[X], texture->width),
				(int)texture_vtx[Y] % texture->height), data);
		texture_vtx[Y] += y_step;
		(*y)++;
	}
}

int	is_door_hit(t_raycast *ray_data, t_data *data)
{
	int	grid[2];

	if (ray_data->vtx_hit == HORZ)
	{
		grid[X] = (int)floor(ray_data->horz_hit[X] / TILE_SIZE);
		grid[Y] = (int)floor(ray_data->horz_hit[Y] / TILE_SIZE);
	}
	else
	{
		grid[X] = (int)floor(ray_data->vert_hit[X] / TILE_SIZE);
		grid[Y] = (int)floor(ray_data->vert_hit[Y] / TILE_SIZE);
	}
	if (get_tile_type(grid, data->map_data) == TILE_DOOR)
	{
		ray_data->door = get_door(grid, data);
		return (1);
	}
	return (0);
}

/**
 * @brief Determines if the door hit by the ray must be rendered or not.
 *
 * This function evaluates whether a door, hit by a ray at position hit[x] and
 * hit[y], should be drawn. It returns different numerical values depending on
 * the situation.
 *
 * @param door Pointer to the door structure.
 * @param hit Array containing the hit position `[x, y]`.
 * @param delta Array representing the direction or step `[dx, dy]`.
 * @return An integer representing the hit status:
 *   - `0` if the current intersection will never be the closest.
 *   - `1` if the door must be drawn.
 *   - `2` if the door is not drawn and the next intersection should be checked.
 *
 * @note The `hit` and `delta` arrays must have at least two elements.
 * @warning Ensure `door` is not NULL before calling this function.
 */
int	door_hit(t_door *door, double hit[2], double delta[2])
{
	if ((door->orient == HORZ && fabs(delta[X]) == TILE_SIZE)
		|| (door->orient == VERT && fabs(delta[Y]) == TILE_SIZE))
		return (0);
	if (door->state == CLOSED)
	{
		hit[X] += (delta[X] / 2.0f);
		hit[Y] += (delta[Y] / 2.0f);
		return (1);
	}
	else if (door->state == OPENED)
		return (2);
	else
	{
		if ((door->orient == HORZ && (hit[X] + delta[X] / 2)
				- (TILE_SIZE * door->grid[X]) <= door->offset)
			|| (door->orient == VERT && (hit[Y] + delta[Y] / 2)
				- (TILE_SIZE * door->grid[Y]) <= door->offset))
			return (2);
		else
		{
			hit[X] += (delta[X] / 2.0f);
			hit[Y] += (delta[Y] / 2.0f);
			return (1);
		}
	}
}
