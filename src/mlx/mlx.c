/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:47:55 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/01 23:50:01 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	game_loop(t_data *data)
{
	void	*new_img_ptr;

	if (data->mlx_data->redraw)
	{
		new_img_ptr = mlx_new_image(data->mlx_data->mlx_ptr, WIDTH, HEIGHT);
		data->mlx_data->new_img_addr
			= mlx_get_data_addr(new_img_ptr, &(data->mlx_data->bpp),
				&(data->mlx_data->line_len), &(data->mlx_data->endian));
		draw_map(data->ray_data, data);
		create_minimap(data->minimap_data, data->mlx_data, data);
		data->mlx_data->redraw = 0;
		mlx_put_image_to_window(data->mlx_data->mlx_ptr,
			data->mlx_data->win_ptr, new_img_ptr, 0, 0);
		if (data->mlx_data->img_ptr)
			mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->img_ptr);
		data->mlx_data->img_ptr = new_img_ptr;
		data->mlx_data->img_addr = data->mlx_data->new_img_addr;
		data->mlx_data->new_img_addr = NULL;
		print_player_info(data); //TEST	
	}
	return (0);
}

// Función que chequea si el personaje puede moverse a la nueva posición
void	check_collision(double *delta, t_data *data)
{
	int	collision[2];
	int	grid[2];

	collision[X] = 0;
	collision[Y] = 0;
	if (delta[X] != 0)
	{
		grid[X] = floor((data->player->pos[X] + delta[X]) / TILE_SIZE);
		grid[Y] = floor(data->player->pos[Y] / TILE_SIZE);
		if (data->map_data->map[grid[Y]][grid[X]] == TILE_WALL)
			collision[X] = 1;
	}
	if (delta[Y] != 0)
	{
		grid[X] = floor(data->player->pos[X] / TILE_SIZE);
		grid[Y] = floor((data->player->pos[Y] + delta[Y]) / TILE_SIZE);
		if (data->map_data->map[grid[Y]][grid[X]] == TILE_WALL)
			collision[Y] = 1;
	}
	if (collision[X] == 1)
		delta[X] = 0;
	if (collision[Y] == 1)
		delta[Y] = 0;
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
		destroy_mlx(data);
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
