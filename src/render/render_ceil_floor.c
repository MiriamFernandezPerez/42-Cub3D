/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceil_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/08 21:06:52 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_ceil(int x, int *y, float hit[2], t_data *data)
{
	int			txt_pixel[2];
	t_texture	*texture;
	int			color;

	texture = get_texture(ID_CEIL, data);
	txt_pixel[X] = (int)(fabs(fmod(hit[X], TILE_SIZE))
			* texture->width / TILE_SIZE) % texture->width;
	txt_pixel[Y] = (int)(fabs(fmod(hit[Y], TILE_SIZE))
			* texture->height / TILE_SIZE) % texture->height;
	color = get_texture_pixel(texture, txt_pixel[X], txt_pixel[Y]);
	print_pixel_render(x, HEIGHT - *y + 1, color, data);
}

void	render_floor_item(int x, int *y, float hit[2], t_data *data)
{
	int			grid[2];
	int			txt_pixel[2];
	t_texture	*texture;
	int			color;

	grid[X] = (int)((hit[X] + (cos(deg_to_rad(data->ray_data->alpha)) * 0.5))
			/ TILE_SIZE);
	grid[Y] = (int)((hit[Y] - (sin(deg_to_rad(data->ray_data->alpha)) * 0.5))
			/ TILE_SIZE);
	if (get_tile_type(grid, data->map_data) == TILE_EXIT)
		texture = get_texture(ID_EXIT, data);
	else
		return ;
	txt_pixel[X] = (int)(fabs(fmod(hit[X], TILE_SIZE))
			* texture->width / TILE_SIZE) % texture->width;
	txt_pixel[Y] = (int)(fabs(fmod(hit[Y], TILE_SIZE))
			* texture->height / TILE_SIZE) % texture->height;
	color = get_texture_pixel(texture, txt_pixel[X], txt_pixel[Y]);
	print_pixel_render(x, *y, color, data);
}

void	render_floor(int x, int *y, float hit[2], t_data *data)
{
	int			txt_pixel[2];
	t_texture	*texture;
	int			color;

	texture = get_texture(ID_FLOOR, data);
	txt_pixel[X] = (int)(fabs(fmod(hit[X], TILE_SIZE))
			* texture->width / TILE_SIZE) % texture->width;
	txt_pixel[Y] = (int)(fabs(fmod(hit[Y], TILE_SIZE))
			* texture->height / TILE_SIZE) % texture->height;
	color = get_texture_pixel(texture, txt_pixel[X], txt_pixel[Y]);
	print_pixel_render(x, *y, color, data);
}

void	raycast_floor(float hit[2], int *y, t_raycast *ray_data, t_data *data)
{
	double	floor_dist;
	double	beta;
	float	corrected_dist;

	beta = ray_data->alpha - data->player->angle;
	beta = normalize_angle(beta);
	if (beta > 180)
		beta = 360 - beta;
	corrected_dist = ray_data->distance_pp / cos(deg_to_rad(beta));
	floor_dist = (TILE_SIZE * corrected_dist) / (2 * (*y - HEIGHT / 2));
	ray_data->pixel_distance = floor_dist;
	hit[X] = data->player->pos[X] + floor_dist
		* cos(deg_to_rad(ray_data->alpha));
	hit[Y] = data->player->pos[Y] - floor_dist
		* sin(deg_to_rad(ray_data->alpha));
}

void	render_ceil_floor(int x, int *y, t_data *data)
{
	float	hit[2];

	raycast_floor(hit, y, data->ray_data, data);
	if (get_texture(ID_FLOOR, data) && get_texture(ID_FLOOR, data)->path)
		render_floor(x, y, hit, data);
	else
		print_pixel_render(x, *y, data->map_data->floor_color, data);
	render_floor_item(x, y, hit, data);
	if (get_texture(ID_CEIL, data) && get_texture(ID_CEIL, data)->path)
		render_ceil(x, y, hit, data);
	else
		print_pixel_render(x, HEIGHT - *y + 1, data->map_data->ceiling_color,
			data);
	(*y)++;
}
