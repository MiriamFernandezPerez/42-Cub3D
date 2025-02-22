/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:47:55 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/04 22:40:37 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Función que chequea si el personaje puede moverse a la nueva posición
void	check_collision(double *delta, t_data *data)
{
	int	grid[2];

	if (delta[X] != 0)
	{
		grid[X] = floor((data->player->pos[X] + delta[X] + copysign(
						(TILE_SIZE * COLLISION_MARGIN), delta[X])) / TILE_SIZE);
		grid[Y] = floor(data->player->pos[Y] / TILE_SIZE);
		if (data->map_data->map[grid[Y]][grid[X]] == TILE_WALL)
			delta[X] = 0;
		if (data->map_data->map[grid[Y]][grid[X]] == TILE_DOOR
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
		if (data->map_data->map[grid[Y]][grid[X]] == TILE_DOOR
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
	check_collision(delta, data);
	data->player->pos[X] += delta[X];
	data->player->pos[Y] += delta[Y];
}

// Evento de teclado para mover al jugador o cambiar el ángulo
int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KEY_LEFT)
		data->player->angle += 5;
	else if (keycode == KEY_RIGHT)
		data->player->angle -= 5;
	else if (keycode == KEY_W)
		move_player(KEY_W, data);
	else if (keycode == KEY_S)
		move_player(KEY_S, data);
	else if (keycode == KEY_A)
		move_player(KEY_A, data);
	else if (keycode == KEY_D)
		move_player(KEY_D, data);
	data->player->angle = normalize_angle(data->player->angle);
	data->mlx_data->redraw = 1;
	return (0);
}

int	close_window(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
