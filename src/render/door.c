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
		if ((door->orient == HORZ
				&& hit[X] - (TILE_SIZE * door->grid[X]) <= door->offset)
			|| (door->orient == VERT
				&& hit[Y] - (TILE_SIZE * door->grid[Y]) <= door->offset))
			return (2);
		else
		{
			hit[X] += (delta[X] / 2.0f);
			hit[Y] += (delta[Y] / 2.0f);
			return (1);
		}
	}
}
