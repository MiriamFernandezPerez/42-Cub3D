/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:13:32 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/18 22:23:44 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_sprite	*get_sprite(int grid[2], t_data *data)
{
	t_sprite	*current;

	current = data->map_data->sprite_list;
	while (current)
	{
		if (current->grid[X] == grid[X] && current->grid[Y] == grid[Y])
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	clear_sprite_list(t_sprite **sprite_list)
{
	if (!(*sprite_list) || !sprite_list)
		return ;
	clear_sprite_list(&(*sprite_list)->next);
	free(*sprite_list);
	*sprite_list = NULL;
}

static t_sprite	*last_node(t_sprite *sprite_list)
{
	if (!sprite_list)
		return (NULL);
	while (sprite_list->next)
	{
		sprite_list = sprite_list->next;
	}
	return (sprite_list);
}

static void	add_node_back(t_sprite **sprite_list, t_sprite *new)
{
	t_sprite	*last;

	if (!sprite_list)
		sprite_list = &new;
	else
	{
		if (!*sprite_list)
			*sprite_list = new;
		else
		{
			last = last_node(*sprite_list);
			last->next = new;
		}
	}
}

void	add_sprite_node(t_sprite_type type, int subtype, int grid[2], t_data *data)
{
	t_sprite	*new;

	new = (t_sprite *)malloc(sizeof(t_sprite));
	if (!new)
		malloc_protection(new, data);
	new->type = type;
	new->subtype = subtype;
	new->grid[X] = grid[X];
	new->grid[Y] = grid[Y];
	new->world[X] = (grid[X] + 0.5) * TILE_SIZE;
	new->world[Y] = (grid[Y] + 0.5) * TILE_SIZE;
	new->size[X] = 0;
	new->size[Y] = 0;
	new->distance = 0.0;
	//TODO segun type/subtype num.texturas (animacion)
	new->txt_num = 1;
	new->next = NULL;
	add_node_back(&data->map_data->sprite_list, new);
}

