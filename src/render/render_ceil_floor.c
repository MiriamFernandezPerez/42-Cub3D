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

void	render_ceil(int x, int *y, float floor[2], t_data *data)
{
	int			txt_pixel[2];
	t_texture	*texture;

	texture = get_texture(ID_CEIL, data);
	txt_pixel[X] = (int)(fabs(fmod(floor[X], TILE_SIZE))
			* texture->width / TILE_SIZE) % texture->width;
	txt_pixel[Y] = (int)(fabs(fmod(floor[Y], TILE_SIZE))
			* texture->height / TILE_SIZE) % texture->height;
	print_pixel_render(x, HEIGHT - *y + 1,
		get_texture_pixel(texture, txt_pixel[X], txt_pixel[Y]), data->mlx_data);
}

void	render_floor_item(int x, int *y, float floor[2], t_data *data)
{
	int			grid[2];
	int			txt_pixel[2];
	t_texture	*texture;

	grid[X] = (int)((floor[X] + (cos(deg_to_rad(data->ray_data->alpha)) * 0.5))
			/ TILE_SIZE);
	grid[Y] = (int)((floor[Y] - (sin(deg_to_rad(data->ray_data->alpha)) * 0.5))
			/ TILE_SIZE);
	if (get_tile_type(grid, data->map_data) == TILE_EXIT)
		texture = get_texture(ID_EXIT, data);
	else
		return ;
	txt_pixel[X] = (int)(fabs(fmod(floor[X], TILE_SIZE))
			* texture->width / TILE_SIZE) % texture->width;
	txt_pixel[Y] = (int)(fabs(fmod(floor[Y], TILE_SIZE))
			* texture->height / TILE_SIZE) % texture->height;
	print_pixel_render(x, *y,
		get_texture_pixel(texture, txt_pixel[X], txt_pixel[Y]), data->mlx_data);
}

void	render_floor(int x, int *y, float floor[2], t_data *data)
{
	int			txt_pixel[2];
	t_texture	*texture;

	texture = get_texture(ID_FLOOR, data);
	txt_pixel[X] = (int)(fabs(fmod(floor[X], TILE_SIZE))
			* texture->width / TILE_SIZE) % texture->width;
	txt_pixel[Y] = (int)(fabs(fmod(floor[Y], TILE_SIZE))
			* texture->height / TILE_SIZE) % texture->height;
	print_pixel_render(x, *y,
		get_texture_pixel(texture, txt_pixel[X], txt_pixel[Y]), data->mlx_data);
}

void	raycast_floor(float floor[2], int *y, t_raycast *ray_data, t_data *data)
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
	floor[X] = data->player->pos[X] + floor_dist
		* cos(deg_to_rad(ray_data->alpha));
	floor[Y] = data->player->pos[Y] - floor_dist
		* sin(deg_to_rad(ray_data->alpha));
}

void	render_ceil_floor(int x, int *y, t_data *data)
{
	float	floor[2];


	raycast_floor(floor, y, data->ray_data, data);
	if (get_texture(ID_FLOOR, data) && get_texture(ID_FLOOR, data)->path)
		render_floor(x, y, floor, data);
	else
		print_pixel_render(x, *y, data->map_data->floor_color,
			data->mlx_data);
	render_floor_item(x, y, floor, data);
	if (get_texture(ID_CEIL, data) && get_texture(ID_CEIL, data)->path)
		render_ceil(x, y, floor, data);
	else
		print_pixel_render(x, HEIGHT - *y + 1, data->map_data->ceiling_color,
			data->mlx_data);
	(*y)++;
}
