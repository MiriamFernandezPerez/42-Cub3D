/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:58:02 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/08 19:19:47 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_texture	*check_door_hit(t_raycast *ray_data, t_data *data)
{
	int	grid[2];

	get_grid_back_hit(grid, ray_data);
	if (get_tile_type(grid, data->map_data) == TILE_DOOR)
		return (get_texture(ID_DOOR, data));
	return (NULL);
}

//Select the correct texture according to the orientation of the wall
t_texture	*get_wall_texture(t_raycast *ray_data, t_data *data)
{
	t_texture	*texture;

	if (ray_data->vtx_hit == HORZ && ray_data->alpha >= 0
		&& ray_data->alpha <= 180)
		texture = get_texture(ID_SOUTH, data);
	else if (ray_data->vtx_hit == HORZ && ray_data->alpha >= 180
		&& ray_data->alpha <= 360)
		texture = get_texture(ID_NORTH, data);
	else if (ray_data->vtx_hit == VERT && ray_data->alpha >= 90
		&& ray_data->alpha <= 270)
		texture = get_texture(ID_WEST, data);
	else if (ray_data->vtx_hit == VERT)
		texture = get_texture(ID_EAST, data);
	if (check_door_hit(ray_data, data))
		texture = check_door_hit(ray_data, data);
	if (!texture)
		ft_error_exit(ERR_LOAD_TXT, data);
	return (texture);
}

void	render_wall(int x, int *y, t_raycast *ray_data, t_data *data)
{
	int			tex[2];
	float		texture_vtx[2];
	float		y_step;
	t_texture	*texture;

	if (ray_data->vtx_hit == HORZ)
		texture_vtx[X] = fmod(ray_data->horz_hit[X], TILE_SIZE);
	else
		texture_vtx[X] = fmod(ray_data->vert_hit[Y], TILE_SIZE);
	texture = get_wall_texture(ray_data, data);
	texture_vtx[X] = (texture_vtx[X] / TILE_SIZE) * texture->width;
	texture_vtx[Y] = 0.0f;
	y_step = (float)texture->height / ray_data->wall_height;
	if (ray_data->wall_height >= HEIGHT)
		texture_vtx[Y] = ((ray_data->wall_height - HEIGHT) / 2) * y_step;
	while (*y >= ray_data->wall_y
		&& *y <= ray_data->wall_y + ray_data->wall_height && *y < HEIGHT)
	{
		tex[Y] = (int)texture_vtx[Y] % texture->height;
		tex[X] = fmod(texture_vtx[X], texture->width);
		print_pixel_render(x, *y, get_texture_pixel(texture,
				tex[X], tex[Y]), data);
		texture_vtx[Y] += y_step;
		(*y)++;
	}
}
