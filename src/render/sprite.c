/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:27:13 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/18 21:01:45 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	get_angle_diff(t_sprite *sprite, t_data *data)
{
	double	delta[2];
	double	beta;
	double	angle_diff;

	delta[X] = sprite->world[X] - data->player->pos[X];
	delta[Y] = data->player->pos[Y] - sprite->world[Y];
	beta = atan2(delta[Y], delta[X]) * (180.0 / M_PI);
	if (beta < 0)
		beta += 360.0;
	angle_diff = beta - data->player->angle;
	if (angle_diff > 180.0)
		angle_diff -= 360.0;
	if (angle_diff < -180.0)
		angle_diff += 360.0;
	return (angle_diff);
}

//Comprobamos que sprites seran visibles en el mapa en el fov actual
void	reset_sprite_visibility(t_map *map_data)
{
	t_sprite	*current;

	current = map_data->sprite_list;
	while (current)
	{
		//current->is_visible = FALSE;
		current->visible_horz = FALSE;
		current->visible_vert = FALSE;
		current->distance = 0.0;
		current->start[X] = 0;
		current->start[Y] = 0;
		current->size[X] = 0;
		current->size[Y] = 0;
		current = current->next;
	}
}

void	set_sprite_visible(int grid[2], int intersection, t_data *data)
{
	t_sprite	*sprite;
	double		angle_diff;

	sprite = get_sprite(grid, data);
	//sprite->is_visible = TRUE;
	if (intersection == HORZ)
		sprite->visible_horz = TRUE;
	else if (intersection == VERT)
		sprite->visible_vert = TRUE;
	sprite->distance = sqrt(pow(data->player->pos[X] - sprite->world[X], 2)
			+ pow(data->player->pos[Y] - sprite->world[Y], 2));
	sprite->size[Y] = ceil((TILE_SIZE * data->ray_data->distance_pp)
			/ sprite->distance);
	sprite->size[X] = sprite->size[Y];
	angle_diff = get_angle_diff(sprite, data);
	angle_diff = angle_diff;
	sprite->start[X] = ((-angle_diff / (FOV / 2.0) * (WIDTH / 2.0))
			+ (WIDTH / 2.0) - (sprite->size[X] / 2.0));
	sprite->start[Y] = HEIGHT / 2.0 - sprite->size[Y] / 2.0;
}
