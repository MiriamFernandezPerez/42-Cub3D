/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/03 19:30:20 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	calculate_corrected_distance(double alpha, t_data *data)
{
	double	beta;

	beta = alpha - data->player->angle;
	beta = normalize_angle(beta);
	if (beta > 180)
		beta = 360 - beta;
	data->ray_data->corrected_distance
		= data->ray_data->shortest_distance * cos(deg_to_rad(beta));
}

void choose_intersection(double distance[2], t_raycast *ray_data, t_data *data)
{
	int	dir[2];
	int	horz[2];
	int	vert[2];
	int	wall[2];

	if (ray_data->alpha > 90 && ray_data->alpha < 270)
		dir[X] = 1;
	else
		dir[X] = -1;
	if (ray_data->alpha > 0 && ray_data->alpha < 180)
		dir[Y] = 1;
	else
		dir[Y] = -1;
	horz[X] = (int)(ray_data->horz_hit[X] / TILE_SIZE);
	horz[Y] = (int)(ray_data->horz_hit[Y] / TILE_SIZE) + dir[Y];
	vert[X] = (int)(ray_data->vert_hit[X] / TILE_SIZE) + dir[X];
	vert[Y] = (int)(ray_data->vert_hit[Y] / TILE_SIZE);
	wall[X] = get_tile_type(vert, data->map_data);
	wall[Y] = get_tile_type(horz, data->map_data);
	if (wall[Y] == TILE_WALL)
		distance[HORZ] = 0;
	else
		distance[VERT] = 0;
}


void	find_shortest_hit_distance(t_player *player, t_raycast *ray_data, t_data *data)
{
	double	distance[2];

	if (ray_data->horz_hit[X] > 0)
		distance[HORZ] = sqrt(pow(player->pos[X] - ray_data->horz_hit[X], 2)
				+ pow(player->pos[Y] - ray_data->horz_hit[Y], 2));
	if (ray_data->vert_hit[X] > 0)
		distance[VERT] = sqrt(pow(player->pos[X] - ray_data->vert_hit[X], 2)
				+ pow(player->pos[Y] - ray_data->vert_hit[Y], 2));
	if (ray_data->vert_hit[X] <= 0)
		ray_data->shortest_distance = distance[HORZ];
	else if (ray_data->horz_hit[X] <= 0)
		ray_data->shortest_distance = distance[VERT];
	else if (distance[HORZ] < distance[VERT])
		ray_data->shortest_distance = distance[HORZ];
	else if (distance[VERT] < distance[HORZ])
		 ray_data->shortest_distance = distance[VERT];
	if (fabs(distance[HORZ] - distance[VERT]) < EPSILON)
	{
		ray_data->shortest_distance = distance[HORZ];
		choose_intersection(distance, ray_data, data);
	}
	if (ray_data->shortest_distance == distance[HORZ])
		ray_data->vtx_hit = X;
	else
		ray_data->vtx_hit = Y;
	//printf("horz_distance: %f\nvert_distance:%f\n", distance[HORZ], distance[VERT]);
}

int get_texture_pixel(t_texture *texture, int x, int y)
{
	char	*pixel;
	int		color;

	if (!texture || x < 0 || y < 0 || x >= texture->width
		|| y >= texture->height)
        return (0x0);
	pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	color = *(int *)pixel;
	//printf("color X:%d Y:%d: %i\n", x, y, color);
	return (color);
}

void	render_wall(int x, int *y, t_raycast *ray_data, t_data *data)
{
	float		texture_vtx[2];
	float		y_step;
	t_texture	*texture;
	int			tex_y;

	//calcular columna de la textura
	if (ray_data->vtx_hit == X)
		texture_vtx[X] = fmod(ray_data->horz_hit[X], TILE_SIZE);
	else
		texture_vtx[X] = fmod(ray_data->vert_hit[Y], TILE_SIZE);
	texture_vtx[X] = (int)(texture_vtx[X] + 0.5);

	//Encontrar textura orientacion
	if (ray_data->vtx_hit == X && ray_data->alpha >= 0 && ray_data->alpha <= 180)
		texture = get_texture(ID_SOUTH, data);
	else if (ray_data->vtx_hit == X && ray_data->alpha >= 180
			&& ray_data->alpha <= 360)
		texture = get_texture(ID_NORTH, data);
	else if (ray_data->vtx_hit == Y && ray_data->alpha >= 90
			&& ray_data->alpha <= 270)
		texture = get_texture(ID_WEST, data);
	else if (ray_data->vtx_hit == Y)
		texture = get_texture(ID_EAST, data);
	//Calculamos texture_x y texture_y
	texture_vtx[X] = (texture_vtx[X] / TILE_SIZE) * texture->width;
	y_step = (float)texture->height / ray_data->wall_height;
	texture_vtx[Y] = 0;
	if (ray_data->wall_height >= HEIGHT)
		texture_vtx[Y] = ((ray_data->wall_height - HEIGHT) / 2) * y_step;
	while (*y >= ray_data->wall_y
		&& *y <= ray_data->wall_y + ray_data->wall_height && *y < HEIGHT)
	{
		tex_y = (int)texture_vtx[Y] % texture->height;
		int tex_x = fmod(texture_vtx[X], texture->width);
		print_pixel_render(x, *y, get_texture_pixel(texture,
			(int)tex_x, tex_y), data->mlx_data);
		texture_vtx[Y] += y_step;
		(*y)++;
	}
	(*y)--;
}

void	render_column(int x, double alpha, t_data *data)
{
	int	y;
	alpha = alpha;


	y = 0;
	while (y < HEIGHT)
	{
		if (y < data->ray_data->wall_y)
			print_pixel_render(
				x, y, data->map_data->ceiling_color, data->mlx_data);
		else if (y >= data->ray_data->wall_y
			&& y <= data->ray_data->wall_y + data->ray_data->wall_height)
			//print_pixel_render(x, y, 0xA95C4C, data->mlx_data);
			render_wall(x, &y, data->ray_data, data);
		else
			print_pixel_render(x, y, data->map_data->floor_color, data->mlx_data);
		y++;
	}
}

void	draw_map(t_raycast *ray_data, t_data *data)
{
	int		x;

	x = 0;
	ray_data->alpha = data->player->angle + FOV / 2;
	ray_data->alpha = normalize_angle(ray_data->alpha);
	while (x < WIDTH)
	{
		//printf("----ALPHA %f -----\n", ray_data->alpha);
		horz_wall_hit(ray_data->alpha, data->player, data);
		vert_wall_hit(ray_data->alpha, data->player, data);
		find_shortest_hit_distance(data->player, data->ray_data, data);
		calculate_corrected_distance(ray_data->alpha, data);
		ray_data->wall_height = ceil((TILE_SIZE * (ray_data->distance_pp))
				/ ray_data->corrected_distance);
		if (ray_data->wall_height < HEIGHT)
			ray_data->wall_y = HEIGHT / 2 - ray_data->wall_height / 2;
		else
			ray_data->wall_y = 0;
		render_column(x, ray_data->alpha, data);
		ray_data->alpha -= ray_data->angle_increment;
		ray_data->alpha = normalize_angle(ray_data->alpha);
		/*printf("----ALPHA %f -----\n", ray_data->alpha);
		printf("horz_hit [X]:%f [Y]:%f\n", ray_data->horz_hit[X], ray_data->horz_hit[Y]);
		printf("vert_hit [X]:%f [Y]:%f\n", ray_data->vert_hit[X], ray_data->vert_hit[Y]);

		printf("------------\n");*/
		x++;
	}
}
