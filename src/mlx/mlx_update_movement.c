/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_update_movement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:39:38 by mirifern          #+#    #+#             */
/*   Updated: 2025/02/07 21:39:40 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	handle_rotation(t_data *data, int *moved)
{
	if (data->mlx_data->keys[ID_KEY_LEFT])
	{
		data->player->angle += 5;
		*moved = 1;
	}
	else if (data->mlx_data->keys[ID_KEY_RIGHT])
	{
		data->player->angle -= 5;
		*moved = 1;
	}
}

void	handle_movement(t_data *data, int *moved)
{
	if (data->mlx_data->keys[ID_KEY_W])
		move_player(KEY_W, data);
	else if (data->mlx_data->keys[ID_KEY_S])
		move_player(KEY_S, data);
	else if (data->mlx_data->keys[ID_KEY_A])
		move_player(KEY_A, data);
	else if (data->mlx_data->keys[ID_KEY_D])
		move_player(KEY_D, data);
	*moved = 1;
}

void	update_movement(t_data *data)
{
	int	moved;

	moved = 0;
	handle_rotation(data, &moved);
	handle_movement(data, &moved);
	if (moved)
	{
		data->player->angle = normalize_angle(data->player->angle);
		data->mlx_data->redraw = 1;
	}
}
