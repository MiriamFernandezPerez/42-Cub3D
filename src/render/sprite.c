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

//Comprobamos que sprites seran visibles en el mapa en el fov actual
void	reset_sprite_visibility(t_map *map_data)
{
	t_sprite	*current;

	current = map_data->sprite_list;
	while (current)
	{
		current->is_visible = FALSE;
		current->distance = 0.0;
		current = current->next;
	}
}

void	set_sprite_visible(int grid[2], t_data *data)
{
	t_sprite	*sprite;
	double			
	sprite = get_sprite(grid, data);
	sprite->is_visible = TRUE;
	sprite->distance = sqrt(pow(data->player->pos[X] - sprite->world[X], 2)
		+ pow(data->player->pos[Y] - sprite->world[Y], 2));
	//Corregir distorsion??
	sprite->size[Y] = ceil((TILE_SIZE / 2 * data->ray_data->distance_pp)
			/ sprite->distance);
	sprite->size[X] = sprite->size[Y];
	printf("Sprite->size[X]:%d [Y]:%d\n", sprite->size[X], sprite->size[Y]);
}
