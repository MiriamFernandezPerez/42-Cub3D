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
	int		delta[2];
	double	beta;
	double	angle_diff;

	delta[X] = abs(sprite->world[X] - data->player->pos[X]);
	delta[Y] = abs(sprite->world[Y] - data->player->pos[Y]);
	printf("delta x:%d Y:%i\n", delta[X], delta[Y]);
	if (delta[Y] == 0 && delta[X] > 0)
		beta = 0;
	else if (delta[Y] == 0)
		beta = 180.0;
	else
		beta = atan2(delta[Y], delta[X]) * (180 / M_PI);
	angle_diff = data->player->angle - beta;
	printf("beta: %f\n", beta);
	angle_diff = fmod(angle_diff + 180, 360) - 180;
	printf("angle_diff:%f\n", angle_diff);
	return (angle_diff);
}

//Comprobamos que sprites seran visibles en el mapa en el fov actual
void	reset_sprite_visibility(t_map *map_data)
{
	t_sprite	*current;

	current = map_data->sprite_list;
	while (current)
	{
		current->is_visible = FALSE;
		current->distance = 0.0;
		current->start[X] = 0;
		current->start[Y] = 0;
		current->size[X] = 0;
		current->size[Y] = 0;
		current = current->next;
	}
}

void	set_sprite_visible(int grid[2], t_data *data)
{
	t_sprite	*sprite;
	double		angle_diff;

	sprite = get_sprite(grid, data);
	sprite->is_visible = TRUE;
	sprite->distance = sqrt(pow(data->player->pos[X] - sprite->world[X], 2)
		+ pow(data->player->pos[Y] - sprite->world[Y], 2));
	//Corregir distorsion??
	sprite->size[Y] = ceil((TILE_SIZE * data->ray_data->distance_pp)
			/ sprite->distance);
	sprite->size[X] = sprite->size[Y];
	//printf("Sprite->size[X]:%d [Y]:%d\n", sprite->size[X], sprite->size[Y]);
	angle_diff = get_angle_diff(sprite, data);
	angle_diff = angle_diff;
	sprite->start[X] = ((angle_diff / FOV) * (WIDTH / 2)) + (WIDTH / 2)
		- (sprite->size[X] / 2);
	sprite->start[Y] = HEIGHT / 2 - sprite->size[Y] / 2;
	printf("pos[X]:%d [Y]:%d\n", sprite->start[X], sprite->start[Y]);

}
