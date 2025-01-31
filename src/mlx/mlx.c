/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:47:55 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/31 21:11:44 by igarcia2         ###   ########.fr       */
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

		//TEST
		print_str(data->mlx_data, 10, 20, "Angle: ");
		print_nbr(data->mlx_data, 60, 20, data->player->angle);
		print_str(data->mlx_data, 10, 40, "Player[X]: ");
		print_nbr(data->mlx_data, 80, 40, data->player->pos[X]);
		print_str(data->mlx_data, 10, 70, "Player[Y]: ");
		print_nbr(data->mlx_data, 80, 70, data->player->pos[Y]);

	}
	return (0);
}

void	move_player(t_player *player, double speed)
{
    double	angle;
	double	dx;
	double	dy;

	angle = player->angle; // Ángulo del jugador en radianes
    
	// Calcular el desplazamiento
    dx = cos(deg_to_rad(angle)) * speed;
    dy = sin(deg_to_rad(angle)) * speed;

    // Actualizar la posición del jugador
    player->pos[X] += ceil(dx);
    player->pos[Y] += ceil(dy * - 1);

    // Si usas un sistema de colisión, verifica que no atraviese muros aquí
}

// Evento de teclado para mover al jugador o cambiar el ángulo
int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC) // Tecla ESC para salir
	{
		destroy_mlx(data);
		free_data(data);
        exit(EXIT_SUCCESS);
	}
	else if (keycode == LEFT)
		data->player->angle += 5;
	else if (keycode == RIGHT)
		data->player->angle -= 5;
	else if (keycode == W)
		move_player(data->player, 5);
	normalize_angle(data->player->angle);
	data->mlx_data->redraw = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == LEFT || keycode == RIGHT)
		data->mlx_data->key_pressed = 0;
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
