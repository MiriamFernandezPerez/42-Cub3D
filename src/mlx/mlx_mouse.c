/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:39:38 by mirifern          #+#    #+#             */
/*   Updated: 2025/02/07 21:39:40 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// Al inicio del juego, como prev_mouse_x se ha inicizlizado en -1, actualizo la variable al valor en el que se encuentra el raton y no hago ninguna rotacion
// En el siguiente movimiento de raton calculo la diferencia en el eje X con la posicion actual del mouse y la almacenada anteriormente y se la asigno a delta_x, el valor del previus_x lo actualizo al valor de x anterior
//Si el valor de delta es diferente de 0, ajusto el ángulo de rotación en función del valor de delta_x multiplicado por el Rotation_Speed que permite regular la sensibilidad del ratón.
//Verifico si estoy en un ángulo válido entre 0 y 2π que es una circunferencia completa, si el ángulo es negativo lo multiplico por 2π para darle la vuelta completa 360º y si es mayor que 2π lo multiplico en negativo
int mouse_handler(int x, int y, t_data *data)
{
    int delta_x;
    (void)y;

    delta_x = 0;
    if (data->mlx_data->mouse_pos)
    {
        data->mlx_data->mouse_pos = 0; 
        return (0); 
    }
    delta_x = x - (WIDTH / 2);
    if (delta_x != 0)
    {
        data->player->angle -= delta_x * ROTATION_SPEED;
           data->player->angle = normalize_angle(data->player->angle);
        data->mlx_data->redraw = 1;
    }
    data->mlx_data->mouse_pos = 1;
    mlx_mouse_move(data->mlx_data->mlx_ptr, data->mlx_data->win_ptr, WIDTH / 2, HEIGHT / 2);
    return (0);
}