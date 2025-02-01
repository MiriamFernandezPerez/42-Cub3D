/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:47:55 by igarcia2          #+#    #+#             */
/*   Updated: 2025/02/01 00:33:01 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	game_loop(t_data *data)
{
	void *new_img_ptr;
	char *new_img_addr;

	if	(data->mlx_data->redraw)
	{
		// 1. Crear la nueva imagen
		new_img_ptr = mlx_new_image(data->mlx_data->mlx_ptr, WIDTH, HEIGHT);
		new_img_addr = mlx_get_data_addr(new_img_ptr, &(data->mlx_data->bpp),
				&(data->mlx_data->line_len), &(data->mlx_data->endian));

		//2. Dibujar en la imagen
		draw_map(data->ray_data, new_img_addr, data);
	
		data->mlx_data->redraw = 0;

		// 3. Proyectar la nueva imagen en la ventana
		mlx_put_image_to_window(data->mlx_data->mlx_ptr,
				data->mlx_data->win_ptr, new_img_ptr, 0, 0);

    	// 4. Destruir la imagen anterior
    	if (data->mlx_data->img_ptr)
			mlx_destroy_image(data->mlx_data->mlx_ptr, data->mlx_data->img_ptr);

		// 5. Actualizar el puntero de la imagen actual
		data->mlx_data->img_ptr = new_img_ptr;
		data->mlx_data->img_addr = new_img_addr;

		print_player_info(data); //TEST	
	}
	return (0);
}

void move_player(int key_pressed, t_player *player)
{
    double	dx;
	double	dy;
    double	direction;
	double	angle;
	
	angle = player->angle;
    direction = 1;
	if (key_pressed == KEY_S)
		direction = -1;
	if (key_pressed == KEY_A)
		angle += 90;
	else if (key_pressed == KEY_D)
		angle -= 90;
	angle = normalize_angle(angle);

    // Calcular desplazamiento
    dx = direction * cos(deg_to_rad(angle)) * PLAYER_SPEED;
    dy = direction * sin(deg_to_rad(angle)) * PLAYER_SPEED * -1;

	if (fabs(dx) < EPSILON)
		dx = 0;
	if (fabs(dy) < EPSILON)
		dy = 0;
    dx = copysign(ceil(fabs(dx)), dx);
    dy = copysign(ceil(fabs(dy)), dy);

    // Actualizar posición del jugador
    player->pos[X] += dx;
    player->pos[Y] += dy;

    // Agregar colisiones 
}

// Evento de teclado para mover al jugador o cambiar el ángulo
int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC) // Tecla ESC para salir
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
		move_player(KEY_W, data->player);
	else if (keycode == KEY_S)
		move_player(KEY_S, data->player);
	else if (keycode == KEY_A)
		move_player(KEY_A, data->player);
	else if (keycode == KEY_D)
		move_player(KEY_D, data->player);

	data->player->angle = normalize_angle(data->player->angle);
	data->mlx_data->redraw = 1;
	return (0);
}

void print_pixel(int x, int y, int color, t_mlx *mlx_data, char *img_addr)
{
	int	pixel;
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return;

    // Calcula la posición en el array de memoria (img_addr)
    pixel = (y * mlx_data->line_len) + (x * (mlx_data->bpp / 8));
    img_addr[pixel] = color & 0xFF;         // Azul
    img_addr[pixel + 1] = (color >> 8) & 0xFF; // Verde
    img_addr[pixel + 2] = (color >> 16) & 0xFF; // Rojo
	if (mlx_data->bpp == 32)
		img_addr[pixel + 3] = (color >> 24); // Transparencia
}
