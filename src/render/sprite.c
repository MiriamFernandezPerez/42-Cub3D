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

int	is_sprite_visible_intersect(t_sprite *sprite, t_data *data)
{
	if (data->ray_data->vtx_hit == HORZ && sprite->visible_horz == TRUE)
		return (TRUE);
	if (data->ray_data->vtx_hit == VERT && sprite->visible_vert == TRUE)
		return (TRUE);
	return (FALSE);
}


t_sprite	*get_closer_sprite(t_sprite *current, t_data *data)
{
	t_sprite	*closer;
	t_sprite	*temp;

	closer = NULL;
	temp = data->map_data->sprite_list;
	while (temp)
	{
		//TODO añadir comprobacion de visibilidad
		if (temp->distance < current->distance
			&& (!closer || temp->distance > closer->distance)
			&& is_sprite_visible_intersect(temp, data))
			closer = temp;
		temp = temp->next;
	}
	return (closer);
}

t_sprite	*get_furthest_sprite(t_data *data)
{
	t_sprite *selected;
	t_sprite *curr;
	
	selected = NULL;
	curr = data->map_data->sprite_list;
	while (curr)
	{
		if (!selected && is_sprite_visible_intersect(curr, data))
		//if (!selected && curr->is_visible)
			selected = curr;

		else if (selected && is_sprite_visible_intersect(curr, data))
		//else if (selected && curr->is_visible)
		{
			if (curr->distance > selected->distance)
				selected = curr;
		}
		curr = curr->next;
	}
	return (selected);
}


int	get_sprite_txt_color(int x, int y, t_sprite *sprite, t_data *data)
{
	int			color;
	double		txt[2];
	t_texture	*texture;

	color = 0x000000;
	//TODO dependiendo del tipo de sprite cogemos textura
	texture = get_texture(ID_EXIT, data);
	txt[X] = (x - sprite->start[X]) / (double)sprite->size[X] * texture->width;
	txt[Y] = (y - sprite->start[Y]) / (double)sprite->size[Y] * texture->height;
	color = get_texture_pixel(texture, fmod(txt[X], texture->width),
		fmod(txt[Y], texture->height));
	return (color);
}

void	render_sprite(int x, int y, t_raycast *ray_data, t_data *data)
{
	(void) ray_data;
	t_sprite	*curr;
	int			color;

	curr = get_furthest_sprite(data);
	if (!curr)
		return ;
	while (curr)
	{
		if (x >= curr->start[X] && x <= curr->start[X] + curr->size[X])
		{
			if (y >= curr->start[Y] && y <= curr->start[Y] + curr->size[Y])
			{
				color = get_sprite_txt_color(x, y, curr, data); 
				print_pixel_render(x, y, color, data);
			}
		}
		curr = get_closer_sprite(curr, data);
	}
}

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
			+ (WIDTH / 2.0)	- (sprite->size[X] / 2.0));
	sprite->start[Y] = HEIGHT / 2.0 - sprite->size[Y] / 2.0;
}
