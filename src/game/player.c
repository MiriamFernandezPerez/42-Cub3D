/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:47:55 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/04 22:40:37 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../inc/audio.h"

void	take_collectable(int grid[2], t_data *data)
{
	t_sprite	*sprite;

	sprite = get_sprite(grid, data);
	if (sprite)
	{
		if (sprite->subtype == T_CHEST)
		{
			play_sound(COLLECT_AUDIO, true, false, data);
			data->player->score += CHEST_SCORE;
			data->map_data->chest_found++;
		}
		else if (sprite->subtype == T_COIN)
		{
			data->map_data->coin_found++;
			data->player->score += COIN_SCORE;
			play_sound(COLLECT_AUDIO, true, false, data);
		}
		else if (sprite->subtype == T_KEY)
		{
			play_sound(KEY_AUDIO, true, false, data);
			data->map_data->key_found++;
		}
		delete_sprite(sprite, data);
		data->map_data->map[grid[Y]][grid[X]] = TILE_FLOOR;
	}
}

void	check_interactable(t_data *data)
{
	int	grid[2];
	int	current_tile;

	grid[X] = data->player->pos[X] / TILE_SIZE;
	grid[Y] = data->player->pos[Y] / TILE_SIZE;
	current_tile = get_tile_type(grid, data->map_data);
	if (ft_strchr(INTERACTABLE_TILES, current_tile))
	{
		if (calculate_distance(data->player->pos[X], data->player->pos[Y],
				(grid[X] + 0.5) * TILE_SIZE, (grid[Y] + 0.5) * TILE_SIZE)
			<= TILE_SIZE / 1.5)
		{
			if (ft_strchr(COLLECTABLE_TILES, current_tile))
				take_collectable(grid, data);
			else if (TILE_EXIT == current_tile)
			{
				play_sound(LEVEL_AUDIO, true, false, data);
				data->player->exit_reached = 1;
			}
		}
	}
}

// Función que chequea si el personaje puede moverse a la nueva posición
void	check_wall_collision(double *delta, t_data *data)
{
	int	grid[2];

	if (delta[X] != 0)
	{
		grid[X] = floor((data->player->pos[X] + delta[X] + copysign(
						(TILE_SIZE * COLLISION_MARGIN), delta[X])) / TILE_SIZE);
		grid[Y] = floor(data->player->pos[Y] / TILE_SIZE);
		if (data->map_data->map[grid[Y]][grid[X]] == TILE_WALL)
			delta[X] = 0;
		if (ft_strchr(DOOR_TILES, data->map_data->map[grid[Y]][grid[X]])
			&& get_door(grid, data)->state != OPENED)
			delta[X] = 0;
	}
	if (delta[Y] != 0)
	{
		grid[X] = floor(data->player->pos[X] / TILE_SIZE);
		grid[Y] = floor((data->player->pos[Y] + delta[Y] + copysign(
						(TILE_SIZE * COLLISION_MARGIN), delta[Y])) / TILE_SIZE);
		if (data->map_data->map[grid[Y]][grid[X]] == TILE_WALL)
			delta[Y] = 0;
		if (ft_strchr(DOOR_TILES, data->map_data->map[grid[Y]][grid[X]])
			&& get_door(grid, data)->state != OPENED)
			delta[Y] = 0;
	}
}

void	move_player(int key_pressed, t_data *data)
{
	double	delta[2];
	double	direction;
	double	angle;

	angle = data->player->angle;
	direction = 1;
	if (key_pressed == KEY_S)
		direction = -1;
	if (key_pressed == KEY_A)
		angle += 90;
	else if (key_pressed == KEY_D)
		angle -= 90;
	angle = normalize_angle(angle);
	delta[X] = direction * cos(deg_to_rad(angle)) * PLAYER_SPEED;
	delta[Y] = direction * sin(deg_to_rad(angle)) * PLAYER_SPEED * -1;
	if (fabs(delta[X]) < EPSILON)
		delta[X] = 0;
	if (fabs(delta[Y]) < EPSILON)
		delta[Y] = 0;
	delta[X] = copysign(ceil(fabs(delta[X])), delta[X]);
	delta[Y] = copysign(ceil(fabs(delta[Y])), delta[Y]);
	check_wall_collision(delta, data);
	data->player->pos[X] += delta[X];
	data->player->pos[Y] += delta[Y];
	check_interactable(data);
}
