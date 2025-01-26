/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:47:55 by igarcia2          #+#    #+#             */
/*   Updated: 2025/01/26 17:20:22 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	game_loop(t_data *data)
{
	if	(data->mlx_data->redraw)
	{
		draw_map(data->ray_data, data);
		data->mlx_data->redraw = 0;
	}
	return (0);
}

// Evento de teclado para mover al jugador o cambiar el ángulo
int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC) // Tecla ESC para salir
	{
		destroy_mlx(data);
		free_data(data);
        exit(EXIT_SUCCESS);
	}
	
	// Cambiar algo en la escena (por ejemplo, ángulo o posición del jugador)
    printf("Tecla presionada: %d\n", keycode);
    data->mlx_data->redraw = 1; // Marcar que la escena necesita ser redibujada
	return (0);
}
